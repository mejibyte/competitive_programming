#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cstdio>

using namespace std;

typedef pair<int, int> Coord;
typedef vector<Coord> Poly;

#define x	first
#define y	second

#define forsn(i, s, n)	for (int i = (s); i < (n); i++)
#define forn(i, n)	forsn (i, 0, n)

#define coord_sub(c1, c2)	Coord((c1).x - (c2).x, (c1).y - (c2).y)

bool cross_prod_sign(const Coord& p, const Coord& q) {
    const long long int pxqy = ((long long int)p.x) * q.y;
    const long long int qxpy = ((long long int)q.x) * p.y;
    return pxqy >= qxpy;
}

bool se_cruzan(const Coord& s0, const Coord& s1, const Coord& t0, const Coord& t1) {
#define se_cruzan1(a, b, c, d) (cross_prod_sign(coord_sub(a, c), coord_sub(d, c)) != cross_prod_sign(coord_sub(b, c), coord_sub(d, c)))
    return se_cruzan1(s0, s1, t0, t1) && se_cruzan1(t0, t1, s0, s1);
#undef se_cruzan1
}

bool esta_adentro(const Coord& punto, const Poly& poly) {
    // buscar un punto afuera
    int maxx = punto.x;
    forn (i, (int)poly.size()) {
        maxx = max(maxx, poly[i].x);
    }
    maxx++;
    const Coord externo(maxx, punto.y + 1);

    // ver si la cantidad de cruces es par o impar
    const int n = poly.size();
    bool adentro = false;
    forn (i, n) adentro ^= se_cruzan(punto, externo, poly[i], poly[(i + 1) % n]);
    return adentro;
}

long long int doble_area(const Poly& poly) {
    const int n = poly.size();
    long long int s = 0;
    forn (i, n) {
        const int j = (i + 1) % n;
        s += ((long long int)poly[i].x) * poly[j].y - ((long long int)poly[i].y) * poly[j].x;
    }
    return s < 0 ? -s : s;
}

typedef vector<int> vint;
typedef vector<long long int> vllint;

vllint __area2;
bool cmp_area2(int i, int j) {
    return __area2[i] < __area2[j];
}
void minwalk(const vector<int>& heights, const vector<Poly>& curves, const Coord& pos_alice, const Coord& pos_bob) {
    const int n = curves.size();

    // ordenar los poligonos por area
    __area2 = vllint(n);
    forn (pi, n) {
        __area2[pi] = doble_area(curves[pi]);
    }
    vint ind(n, 0);
    forn (i, n) ind[i] = i;
    sort(ind.begin(), ind.end(), cmp_area2);

    // visitarlos en ese orden y calcular cuanto sube / baja
#define up_down(H1, H2)	if (H1 < H2) { cost_up += H2 - H1; } else { cost_down += H1 - H2; }
    int last_height_alice = -1, last_height_bob = -1;
    int cost_up = 0, cost_down = 0;
    forn (i, n) {
        const int j = ind[i];
        const bool contains_alice = esta_adentro(pos_alice, curves[j]);
        const bool contains_bob = esta_adentro(pos_bob, curves[j]);
        if (contains_alice && contains_bob) {
            break;
        } else if (contains_alice) {
            if (last_height_alice != -1) {
                up_down(last_height_alice, heights[j]);
            }
            last_height_alice = heights[j];
        } else if (contains_bob) {
            if (last_height_bob != -1) {
                up_down(heights[j], last_height_bob);
            }
            last_height_bob = heights[j];
        }
    }
    if (last_height_alice != -1 && last_height_bob != -1) {
        up_down(last_height_alice, last_height_bob);
    }
    printf("%i %i\n", cost_up, cost_down);
}

int main() {
    const Coord pos_alice(0, 0);
    const Coord pos_bob(100000, 0);
    int ncases;
    scanf("%i\n", &ncases);
    forn (ci, ncases) {
        int npolys;
        scanf("%i\n", &npolys);

        vector<Poly> polys;
        vector<int> heights;
        forn (pi, npolys) {
            int curve_height, nverts;
            scanf("%i %i", &curve_height, &nverts);
            polys.push_back(Poly());
            forn (vi, nverts) {
                int vert_x, vert_y;
                scanf("%i %i", &vert_x, &vert_y);
                polys[pi].push_back(Coord(vert_x, vert_y));
            }
            heights.push_back(curve_height);
        }

        minwalk(heights, polys, pos_alice, pos_bob);
    }
    return 0;
}

