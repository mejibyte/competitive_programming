// Andrés Mejía
using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

int x[8], y[8];

typedef pair<int, int> point;
typedef vector< point > polygon;

int cross(point a, point b) {
    return a.first * b.second - a.second * b.first;
}

point sub(point a, point b) {
    return make_pair(a.first - b.first, a.second - b.second);
}

int dot(point a, point b) {
    return a.first * b.first + a.second * b.second;
}

bool parallel(point p0, point p1,    point p2, point p3) {
    point a = make_pair(p1.first - p0.first, p1.second - p0.second);
    point b = make_pair(p3.first - p2.first, p3.second - p2.second);
    return cross(a, b) == 0;
}

bool collineal(point a, point b, point c) {
    point u = sub(b, a);
    point v = sub(c, a);
    return cross(u, v) == 0;
}

bool positiveArea(polygon p) {
    for (int i = 0; i < p.size(); ++i) {
        for (int j = i + 1; j < p.size(); ++j) {
            for (int k = j + 1; k < p.size(); ++k) {
                if (collineal(p[0], p[1], p[2])) return false;
            }
        }
    }
    return true;
}

bool rectangle(int m) {
    vector< pair<int, int> > p;
    for (int i = 0; i < 8; ++i) {
        if (m & (1 << i)) {
            p.push_back(make_pair(x[i], y[i]));
        }
    }
    assert(p.size() == 4);
    sort(p.begin(), p.end());
    do {
        if (parallel(p[0], p[1], p[2], p[3]) and parallel(p[0], p[2], p[1], p[3]) and positiveArea(p)) {
            if (dot(sub(p[1], p[0]), sub(p[3], p[1])) == 0) return true;
            return false;
        }
    } while(next_permutation(p.begin(), p.end()));
    return false;
}


bool square(int m) {
    vector< pair<int, int> > p;
    for (int i = 0; i < 8; ++i) {
        if (m & (1 << i)) {
            p.push_back(make_pair(x[i], y[i]));
        }
    }
    assert(p.size() == 4);

    
    if (!rectangle(m)) return false;
    vector<double> dist;
    for (int i = 0; i < p.size(); ++i) {
        for (int j = i + 1; j < p.size(); ++j) {
            dist.push_back(  hypot(p[i].first - p[j].first,  p[i].second - p[j].second)  );
        }
    }
    assert(dist.size() == 6);
    sort(dist.begin(), dist.end());
    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            if (cmp(dist[i], dist[j]) != 0) return false;
        }
    }
    if (cmp(dist[3], dist[4]) == 0) return false;
    if (cmp(dist[4], dist[5]) != 0) return false;
    if (cmp(dist[3]))

    return true;
}

int main(){
    for (int i = 0; i < 8; ++i) cin >> x[i] >> y[i];
    for (int m = 1; m < 1 << 8; ++m) {
        if (__builtin_popcount(m) != 4) continue;
        if (square(m) and rectangle(~m)) {
            puts("YES");
            for (int i = 0; i < 8; ++i) {
                if (m & (1 << i)) {
                    printf("%d ", i + 1);
                }
            }
            puts("");
            for (int i = 0; i < 8; ++i) {
                if (~m & (1 << i)) {
                    printf("%d ", i + 1);
                }
            }
            puts("");
            return 0;
        }
    }
    puts("NO");
    return 0;
}