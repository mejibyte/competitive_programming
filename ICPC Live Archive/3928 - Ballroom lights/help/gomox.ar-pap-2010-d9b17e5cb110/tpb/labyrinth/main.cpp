#include <iostream>
#include <vector>
#include <cassert>
#include <cstdio>

using namespace std;

#define forsn(i, s, n)	for (int i = (s); i < (n); i++)
#define forn(i, n)	forsn (i, 0, n)

typedef vector<bool> vbool;
typedef vector<vbool> vvbool;

typedef int Node;
int rows;
int cols;
vvbool mapa;

#define node(r, c)		((r) << 12 | (c))
#define node_row(v)		((v) >> 12)
#define node_col(v)		((v) & 0xfff)

#define NONE			0xffffffff

Node vecino(bool ns, Node v) {
#define sig(x)	((x) ? 1 : -1)
	const int r = node_row(v) - ns, c = node_col(v);
	if (r < 0 || r >= rows) return NONE;
	const int cc = c + sig(ns ^ mapa[r][c]);
	if (cc < 0 || cc >= cols) return NONE;
	const int rr = node_row(v) + sig(ns) * -!(mapa[r][c] ^ mapa[r][cc]);
	if (rr < 0 || rr > rows) return NONE;
	return node(rr, cc);
}

int resolver() {
#define marcado(v)	(_marcas[node_row(v)][node_col(v)])
#define marcar(v)	(_marcas[node_row(v)][node_col(v)] = true)
	int cant = 0;
	vvbool _marcas(rows + 1, vbool(cols, false));
	forn (c, cols) {
		Node v = node(0, c);

		if (marcado(v)) continue;
		marcar(v);

		for (;;) {
			Node w = NONE;
			forn (direction, 2) {
				Node vv = vecino(direction, v);
				if (vv == NONE || marcado(vv)) continue;
				assert(w == NONE);
				w = vv;
			}
			if (w == NONE) break;
			if (node_row(w) == rows) {
				cant++;
				break;
			}
			marcar(w);
			v = w;
		}
	}
	return cant;
}

int main() {
	int ncases;
	cin >> ncases;
	
	forn (i, ncases) {
		cin >> cols >> rows;
		mapa = vvbool(rows, vbool(cols));
		forn (r, rows) {
			forn (c, cols) {
				char mapa_rc;
				cin >> mapa_rc;
				mapa[r][c] = (mapa_rc == '\\');
			}
		}

		cout << resolver() << endl;
	}

	return 0;
}
