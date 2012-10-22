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
#include <bitset>
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

struct Segment {
    int r1, c1, r2, c2;
    Segment(int x1, int y1, int x2, int y2) : r1(x1), c1(y1), r2(x2), c2(y2) {
        assert(r1 != r2 or c1 != c2);
        assert(r1 == r2 or c1 == c2);
    }
    
    bool horizontal() const {
        return r1 == r2;
    }
    
    bool vertical() const {
        return c1 == c2;
    }
    
    int length() const {
        return horizontal() ? c2 - c1 + 1 : r2 - r1 + 1;
    }
};

int intersection(Segment a, Segment b) {
    if (a.vertical() and b.vertical()) {
        if (a.c1 != b.c1) return 0; // vertical on different columns
        int r1 = max(a.r1, b.r1);
        int r2 = min(a.r2, b.r2);
        return r1 <= r2 ? r2 - r1 + 1 : 0;
    } else if (a.horizontal() and b.horizontal()) {
        if (a.r1 != b.r1) return 0; // horizontal on different rows
        int c1 = max(a.c1, b.c1);
        int c2 = min(a.c2, b.c2);
        return c1 <= c2 ? c2 - c1 + 1 : 0;
    } else { // one vertical and one horizontal
        if (b.vertical()) swap(a, b);
        assert(a.vertical() and b.horizontal());
        if (b.c1 <= a.c1 and a.c1 <= b.c2 and a.r1 <= b.r1 and b.r1 <= a.r2) return 1;
        return 0;
    }
}

int R, C, P;

int main(){
    
    return 0;
}