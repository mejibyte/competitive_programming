#include <iostream>
#include <cmath>
#include <cstdio>
#include <list>
#include <utility>
#include <cstdlib>
#include <cassert>
#include <complex>

#define forn(i, n) for (int i = 0; i < (n); i++)
#define EPS 1e-8

using namespace std;

struct Vector {
    long double x;
    long double y;

    Vector(long double xi, long double yi): x(xi), y(yi) {};

    long double length()  {
        return hypot(x, y);
    }

    long double angle() {
        return atan2(y, x);
    }

};

struct Column {
    Vector position;
    long double radius;

    Column(long double x, long double y, long double r) : position(x,y), radius(r) {};
};

typedef Vector Lamp;
typedef pair<long double, long double> Interval;
typedef pair<Vector, Vector> Segment;


inline long double length(const Segment& s) {
    return Vector(s.second.x - s.first.x, s.second.y - s.first.y).length();
}

inline long double length(const Interval& i) {
    assert(i.first <= i.second);
    return i.second - i.first;
}


pair< long double, bool > intersect_segments(const Segment& s1, const Segment& s2) {
    Vector p1 = s1.first;
    Vector p2 = s1.second;
    Vector p3 = s2.first;
    Vector p4 = s2.second;

    long double den = (p4.y-p3.y)*(p2.x-p1.x) - (p4.x-p3.x)*(p2.y-p1.y);

    long double ua_num = (p4.x-p3.x)*(p1.y-p3.y) - (p4.y-p3.y)*(p1.x-p3.x);
    long double ub_num = (p2.x-p1.x)*(p1.y-p3.y) - (p2.y-p1.y)*(p1.x-p3.x);

    if (fabs(den) < EPS) {
        // Caso en que los Segments son paralelos
        if (fabs(ua_num - ub_num) < EPS && fabs(ub_num) < EPS) {
            // Las rectas son coincidentes, esto no deberia ocurrir
            assert(false);
        }
        return make_pair(0, false);
    }

    if (ub_num/den >= 0) {
        return make_pair(ua_num/den, true);
    }
    return make_pair(0, false);
}


Interval intersect_intervals(const Interval& i1, const Interval& i2) {

    long double d0 = max(i1.first, i2.first);
    long double d1 = min(i1.second, i2.second);

    if (d1 < d0) {
        return Interval(0, 0);
    } else {
        return Interval(d0, d1);
    }
}


Interval dark_range(const Segment& wall, const Lamp& lamp, const Column& column) {
    Vector bisectriz(column.position.x - lamp.x, column.position.y - lamp.y);
    long double p = asin(column.radius/bisectriz.length());
    long double alpha = bisectriz.angle();

    Vector d1(cos(alpha + p), sin(alpha + p));
    Vector d2(cos(alpha - p), sin(alpha - p));

    pair< long double, bool > p1 = intersect_segments(wall, Segment(lamp, Vector(lamp.x + d1.x, lamp.y + d1.y)));
    pair< long double, bool > p2 = intersect_segments(wall, Segment(lamp, Vector(lamp.x + d2.x, lamp.y + d2.y)));

    long double wall_length = length(wall);

    // Se sabe que los puntos de interseccion estan ordenados correctamente
    // porque el angulo de diferencia entre las semirectas es menor a 180,
    // entonces no es necesario chequearlo.
    Interval res;

    if (!p1.second) {
        if (!p2.second) {
            return Interval(0, 0);
        } else {
            res = Interval(0, p2.first);
        }
    } else {
        if (!p2.second) {
            res = Interval(p1.first, 1);
        } else {
            res = Interval(p1.first, p2.first);
        }
    }

    res = intersect_intervals(res, Interval(0,1));
    return Interval(res.first * wall_length, res.second * wall_length);
}

void invert_range(const list<Interval>& ints, long double fin, list<Interval>& out) {

    if (!ints.size()) {
        out.push_back(Interval(0,fin));
        return;
    }


    list<Interval>::const_iterator it = ints.begin();
    if (it->first > 0) {
        out.push_back(Interval(0, it->first));
    }

    it++;

    list<Interval>::const_iterator itprev = ints.begin();
    while (it != ints.end()) {
        out.push_back(Interval(itprev->second, it->first));
        it++;
        itprev++;
    }

    if (itprev->second < fin) {
        out.push_back(Interval(itprev->second, fin));
    }
}


void reduce_union(list<Interval>& l_o, list<Interval>& out) {
    // elimino repetidos para acelerar el sort
    list<Interval> l;

    for (list<Interval>::const_iterator it = l_o.begin(); it != l_o.end(); it++) {
        if (it->first < it->second) {
            l.push_back(Interval(it->first, it->second));
        } else if (it->first > it->second) {
            assert(false);
        }
    }


    if (!l.size()) return;

    l.sort();

    list<Interval>::const_iterator it = l.begin();
    Interval cand = *it;
    Interval other;

    it++;
    while (it != l.end()) {
        other = *it;
        if (other.first < other.second) {
            if (other.first > cand.second) {
                out.push_back(cand);
                cand = other;
            } else {
                if (other.second > cand.second) {
                    cand = Interval(cand.first, other.second);
                }
            }
        }
        it++;
    }

    out.push_back(cand);
}


long double solve(const list<Lamp>& lamps, const list<Column>& columns, int max_x, int max_y) {
    list<Segment> walls;
    walls.push_back(Segment(Vector(max_x,0), Vector(0, 0)));

    long double total = 0;

    for (list<Segment>::iterator p = walls.begin(); p != walls.end(); p++) {
        list<Interval> lit_on_this_wall;
        for (list<Lamp>::const_iterator l = lamps.begin(); l != lamps.end(); l++) {
            list<Interval> dark_zones;
            for (list<Column>::const_iterator c = columns.begin(); c != columns.end(); c++) {
                dark_zones.push_back(dark_range(*p, *l, *c));
            }

            list<Interval> merged_dark_zones;
            list<Interval> lit_zone;

            reduce_union(dark_zones, merged_dark_zones);
            invert_range(merged_dark_zones, length(*p), lit_zone);

            lit_on_this_wall.splice(lit_on_this_wall.end(), lit_zone);
        }

        list<Interval> merged_lit_on_this_wall;
        reduce_union(lit_on_this_wall, merged_lit_on_this_wall);

        for (list<Interval>::iterator it = merged_lit_on_this_wall.begin(); it != merged_lit_on_this_wall.end(); it++) {
            total += length(*it);
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

        list<Vector> lamps;
        list<Column> columns;

        int x, y, r;

        forn(i, nl) {
            scanf("%d %d", &x, &y);
            lamps.push_back(Lamp(x,y));
        }

        forn(i, nc) {
            scanf("%d %d %d", &x, &y, &r);
            columns.push_back(Column(x, y, r));
        }

        printf("%.4Lf\n", solve(lamps, columns, max_x, max_y));
    }
}
