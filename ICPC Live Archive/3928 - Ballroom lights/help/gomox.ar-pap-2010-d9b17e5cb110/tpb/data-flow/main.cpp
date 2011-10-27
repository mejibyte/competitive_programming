
#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <cassert>

using namespace std;

typedef long long int int64;

#define forsn(i, s, n)	for (int64 i = (s); i < (n); i++)
#define forn(i, n)	forsn (i, 0, n)
#define forall(x, s)	for (typeof((s).begin()) x = (s).begin(); x != (s).end(); x++)

typedef vector<int64> vint;
typedef vector<vint> vvint;

int64 n;
int64 capacidad_eje0;
int64 capacidad_enlace;
vvint grafo;  // listas de adyacencia
vvint costo;  // matriz
vvint flujo;  // matriz

#define agregar(u, v, c) { \
	grafo[u].push_back(v); \
	costo[u][v] = (c); \
	grafo[v].push_back(u); \
	costo[v][u] = (c); \
}

#define capacidad(v, w) (((v) == 0 || (w) == 0) ? capacidad_eje0 : capacidad_enlace)

void print_grafo_residual() {
	cout << "---------------" << endl;
	forn (v, n) {
		cout << v << endl;
		forall (vecino, grafo[v]) {
			cout << "--> ";
			cout << *vecino;
			cout << " costo = " << costo[v][*vecino];
			cout << " flujo = " << flujo[v][*vecino] << " / " << capacidad(v, *vecino);
			cout << endl;
		}
		cout << endl;
	}
}

#define INF 0x7fffffff
#define No_hay_camino	-1
#define signo(x)	((x) < 0 ? -1 : 1)
int64 caumento(vint& camino) {
	// buscar el camino de aumento de costo minimo usando Bellman-Ford
	vint dist(n, INF);
	vint ant(n, -1);

	dist[0] = 0;

	forn (it, n - 1) {
		// para cada arista del grafo residual
		bool cambio = false;
		forn (v, n) forall (vecino, grafo[v]) {
			const int64 w = *vecino;
			if (capacidad(v, w) - flujo[v][w] <= 0) continue;
			if (dist[v] == INF) continue;
			int64 ndist = dist[v] + signo(flujo[v][w]) * costo[v][w];
			if (ndist < dist[w]) {
				dist[w] = ndist;
				ant[w] = v;
				cambio = true;
			}
		}
		if (!cambio) break;
	}

	// armar el camino
	int64 costo_camino = 0;
	int64 actual = n - 1;
	while (true) {
		camino.push_back(actual);
		int64 anterior = ant[actual];
		if (anterior == -1) break;
		costo_camino += signo(flujo[anterior][actual]) * costo[anterior][actual];
		actual = anterior;
	}
	if (actual == 0) {
		return costo_camino;
	} else {
		return No_hay_camino;
	}
}

int64 resolver() {
	int64 flujo_total = 0;
	int64 costo_total = 0;
	while (flujo_total < capacidad_eje0) {
		//print_grafo_residual();
		vint camino_aumento;
		int64 costo_camino = caumento(camino_aumento);
		if (costo_camino == No_hay_camino) return No_hay_camino;
		// saturar el camino de aumento
		int64 mn = INF;
		
		forn (i, camino_aumento.size() - 1) {
			const int64 v = camino_aumento[i + 1], w = camino_aumento[i];
			if (flujo[v][w] < 0) {
				mn = min(mn, -flujo[v][w]);
			} else {
				mn = min(mn, capacidad(v, w) - flujo[v][w]);
			}
		}
		forn (i, camino_aumento.size() - 1) {
			const int64 v = camino_aumento[i + 1], w = camino_aumento[i];
			flujo[v][w] += mn;
			flujo[w][v] -= mn;
		}
		if (mn == 0) return No_hay_camino;
		flujo_total += mn;
		costo_total += costo_camino * mn;
	}

	return costo_total;
}

int main() {
	int64 m;
	while (cin >> n >> m) {
		n++;
		grafo = vvint(n, vint());
		costo = vvint(n, vint(n, 0));
		flujo = vvint(n, vint(n, 0));

		agregar(0, 1, 0);
		forn (i, m) {
			int64 v1, v2, c;
			cin >> v1 >> v2 >> c;
			agregar(v1, v2, c);
		}
		cin >> capacidad_eje0 >> capacidad_enlace;
		int64 r = resolver();
		if (r == No_hay_camino) {
			cout << "Impossible." << endl;
		} else {
			cout << r << endl;
		}
	}
	return 0;
}

