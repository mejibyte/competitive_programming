#include <iostream>
#include <cmath>
#include <cstdio>
#include <list>
#include <utility>
#include <cstdlib>
#include <cassert>
#include <complex>

#define forn(i, n) for (int i = 0; i < (n); i++)
#define TOLERANCIA 1e-8

using namespace std;

struct MaybeDouble {
    long double valor;
    bool valido;

    MaybeDouble(long double v, bool b): valor(v), valido(b) {};
};

struct Vector {
    long double x;
    long double y;

    Vector(long double xi, long double yi): x(xi), y(yi) {};

    long double norma()  {
        return hypot(x, y);
    }

    long double angulo() {
        return atan2(y, x);
    }

};

struct Columna {
    Vector posicion;
    long double radio;

    Columna(long double x, long double y, long double r) : posicion(x,y), radio(r) {};
};

typedef Vector Lampara;
typedef pair<long double, long double> Intervalo;
typedef pair<Vector, Vector> Segmento;


inline long double largo(const Segmento& s) {
    return Vector(s.second.x - s.first.x, s.second.y - s.first.y).norma();
}

inline long double largo(const Intervalo& i) {
    assert(i.first <= i.second);
    return i.second - i.first;
}


MaybeDouble intersect_segments(const Segmento& s1, const Segmento& s2) {
    Vector p1 = s1.first;
    Vector p2 = s1.second;
    Vector p3 = s2.first;
    Vector p4 = s2.second;

    long double den = (p4.y-p3.y)*(p2.x-p1.x) - (p4.x-p3.x)*(p2.y-p1.y);

    long double ua_num = (p4.x-p3.x)*(p1.y-p3.y) - (p4.y-p3.y)*(p1.x-p3.x);
    long double ub_num = (p2.x-p1.x)*(p1.y-p3.y) - (p2.y-p1.y)*(p1.x-p3.x);

    if (fabs(den) < TOLERANCIA) {
        // Caso en que los segmentos son paralelos
        if (fabs(ua_num - ub_num) < TOLERANCIA && fabs(ub_num) < TOLERANCIA) {
            // Las rectas son coincidentes, esto no deberia ocurrir
            assert(false);
            return MaybeDouble((p1.norma() > p2.norma()? 0 : 1), true);
        }
        return MaybeDouble(0, false);
    }

    if (ub_num/den >= 0) {
        return MaybeDouble(ua_num/den, true);
    }
    return MaybeDouble(0, false);
}


Intervalo interseccion_intervalos(const Intervalo& i1, const Intervalo& i2) {

    long double d0 = max(i1.first, i2.first);
    long double d1 = min(i1.second, i2.second);

    if (d1 < d0) {
        return Intervalo(0, 0);
    } else {
        return Intervalo(d0, d1);
    }
}


Intervalo rango_oscurecido(const Segmento& pared, const Lampara& lampara, const Columna& columna) {
    Vector bisectriz(columna.posicion.x - lampara.x, columna.posicion.y - lampara.y);
    long double p = asin(columna.radio/bisectriz.norma());
    long double alpha = bisectriz.angulo();

    Vector d1(cos(alpha + p), sin(alpha + p));
    Vector d2(cos(alpha - p), sin(alpha - p));

    MaybeDouble p1 = intersect_segments(pared, Segmento(lampara, Vector(lampara.x + d1.x, lampara.y + d1.y)));
    MaybeDouble p2 = intersect_segments(pared, Segmento(lampara, Vector(lampara.x + d2.x, lampara.y + d2.y)));

    long double unidad = largo(pared);

    // Se sabe que los puntos de interseccion estan ordenados correctamente
    // porque el angulo de diferencia entre las semirectas es menor a 180,
    // entonces no es necesario chequearlo.
    Intervalo res;

    if (!p1.valido) {
        if (!p2.valido) {
            return Intervalo(0, 0);
        } else {
            res = Intervalo(0, p2.valor);
        }
    } else {
        if (!p2.valido) {
            res = Intervalo(p1.valor, 1);
        } else {
            res = Intervalo(p1.valor, p2.valor);
        }
    }

    res = interseccion_intervalos(res, Intervalo(0,1));
    return Intervalo(res.first * unidad, res.second * unidad);
}

void invertir_rango(const list<Intervalo>& ints, long double fin, list<Intervalo>& out) {

    if (!ints.size()) {
        out.push_back(Intervalo(0,fin));
        return;
    }


    list<Intervalo>::const_iterator it = ints.begin();
    if (it->first > 0) {
        out.push_back(Intervalo(0, it->first));
    }

    it++;

    list<Intervalo>::const_iterator itprev = ints.begin();
    while (it != ints.end()) {
        out.push_back(Intervalo(itprev->second, it->first));
        it++;
        itprev++;
    }

    if (itprev->second < fin) {
        out.push_back(Intervalo(itprev->second, fin));
    }
}


void reduce_union(list<Intervalo>& l_o, list<Intervalo>& out) {
    // elimino repetidos para acelerar el sort
    list<Intervalo> l;

    for (list<Intervalo>::const_iterator itcito = l_o.begin(); itcito != l_o.end(); itcito++) {
        if (itcito->first < itcito->second) {
            l.push_back(Intervalo(itcito->first, itcito->second));
        } else if (itcito->first > itcito->second) {
            assert(false);
        }
    }


    if (!l.size()) return;

    l.sort();

    list<Intervalo>::const_iterator it = l.begin();
    Intervalo cand = *it;
    Intervalo otro;

    it++;
    while (it != l.end()) {
        otro = *it;
        if (otro.first < otro.second) {
            if (otro.first > cand.second) {
                out.push_back(cand);
                cand = otro;
            } else {
                if (otro.second > cand.second) {
                    cand = Intervalo(cand.first, otro.second);
                }
            }
        }
        it++;
    }

    out.push_back(cand);
}


long double resolver(const list<Lampara>& lamparas, const list<Columna>& columnas, int max_x, int max_y) {
    list<Segmento> paredes;
    paredes.push_back(Segmento(Vector(0,0), Vector(0, max_y)));
    paredes.push_back(Segmento(Vector(0,max_y), Vector(max_x, max_y)));
    paredes.push_back(Segmento(Vector(max_x,max_y), Vector(max_x, 0)));
    paredes.push_back(Segmento(Vector(max_x,0), Vector(0, 0)));

    long double total = 0;

    for (list<Segmento>::iterator p = paredes.begin(); p != paredes.end(); p++) {
        list<Intervalo> luces_pared;
        for (list<Lampara>::const_iterator l = lamparas.begin(); l != lamparas.end(); l++) {
            list<Intervalo> zonas_tapadas;
            for (list<Columna>::const_iterator c = columnas.begin(); c != columnas.end(); c++) {
                zonas_tapadas.push_back(rango_oscurecido(*p, *l, *c));
            }

            list<Intervalo> tapadas_unidas;
            list<Intervalo> zona_iluminada;

            reduce_union(zonas_tapadas, tapadas_unidas);
            invertir_rango(tapadas_unidas, largo(*p), zona_iluminada);

            luces_pared.splice(luces_pared.end(), zona_iluminada);
        }

        list<Intervalo> luces_pared_unidas;
        reduce_union(luces_pared, luces_pared_unidas);

        for (list<Intervalo>::iterator it = luces_pared_unidas.begin(); it != luces_pared_unidas.end(); it++) {
            total += largo(*it);
        }
    }

    return total;
}


int main() {

    int nl, nc, max_x, max_y;

    for (;;) {
        scanf("%d %d %d %d", &nl, &nc, &max_x, &max_y);

        if (!(nl || nc || max_x || max_y)) {
            break;
        }

        list<Vector> lamparas;
        list<Columna> columnas;

        int x, y, r;

        forn(i, nl) {
            scanf("%d %d", &x, &y);
            lamparas.push_back(Lampara(x,y));
        }

        forn(i, nc) {
            scanf("%d %d %d", &x, &y, &r);
            columnas.push_back(Columna(x, y, r));
        }

        printf("%.4Lf\n", resolver(lamparas, columnas, max_x, max_y));
    }
}
