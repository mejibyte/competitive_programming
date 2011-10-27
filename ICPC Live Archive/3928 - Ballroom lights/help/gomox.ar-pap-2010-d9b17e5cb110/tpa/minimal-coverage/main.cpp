#include <stdio.h>
#include <iostream>
#include <list>

using namespace std;

#define foreachin(it,s) for (typeof(s.begin()) it = (s).begin(); it != (s).end(); it++)

typedef pair<int, int> Intervalo;
typedef list<Intervalo> LIntervalo;

bool compararPorPrimeraComp(const Intervalo& p1, const Intervalo& p2){
	return p1.first < p2.first;
}

bool resolver(LIntervalo& intervalos, int limite, LIntervalo& solucion) {
	intervalos.sort(compararPorPrimeraComp);
	int final = 0; // mayor coordenada cubierta hasta ahora
	int r_i = 0;   // mayor coordenada hasta ahora alcanzada
	Intervalo parActual = Intervalo(0, 0); // posible candidato a ser agregado

	foreachin (it, intervalos) {
		// si la primera componente esta mayor que final, ya miramos
		// todo el C, entonces hay que agregar el intervalo
		if (it->first > final) {
			solucion.push_back(parActual);
			final = r_i; // muevo el borde final
		}
		// si la primera componente es menor que final miro si el intervalo sirve
		if (it->first <= final) {
			// sirve si llega mas lejos que lo que hay hasta ahora
			if (it->second > r_i) {
				r_i = it->second;
				parActual = *it;
				// si ademas ya llegue al limite, termine
				if (r_i >= limite) {
					solucion.push_back(parActual);
					break;
				} 
			}
		} else {
			// hay un hueco que no puedo cubrir con ningun intervalo
			break;
		}
	}

	return r_i >= limite;
}

int main(int argc, char **argv)
{
	int casos;
	cin >> casos;
	while (casos > 0) {
		casos--;
		int limite, x, y;
		cin >> limite;
		x = 1;
		y = 1;
		// cargo intervalos
		LIntervalo intervalos;
		while (y != 0 || x != 0) {
			scanf ("%d %d", &x, &y);
			if (x != 0 || y != 0) {
				if (x < y) { //para no cargar intervalos inutiles
					intervalos.push_front(Intervalo(x,y));
				}
			}
		}
		// resuelvo instancia
		LIntervalo solucion;
		if (resolver(intervalos, limite, solucion)) {
			cout << solucion.size() << endl;
			foreachin (it, solucion) {
				cout << it->first << " " << it->second << endl;
			}
		} else {
			cout << 0 << endl;
		}
		cout << endl;
	}
}

