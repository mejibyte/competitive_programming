// Andrés Mejía

// Accepted

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

const int MAXN = 2005;

struct Tree {
    int x, y, value;
    int color;
};

Tree trees[MAXN], v[MAXN];

inline bool above(const Tree &t) {
    if (t.x == 0 and t.y == 0) printf("t = (%d, %d)\n", t.x, t.y);
    assert(t.x != 0 or t.y != 0);
    if (t.y == 0) return t.x > 0;
    return t.y > 0;
}

inline bool below(const Tree &t) {
    return !above(t);
}


bool compare(const Tree &a, const Tree &b) {
    long long cross = 1LL * a.x * b.y - 1LL * a.y * b.x;
    if (!above(a)) cross = -cross;
    if (!above(b)) cross = -cross;
    return cross > 0;
}

bool equal(const Tree &a, const Tree &b) {
    long long cross = 1LL * a.x * b.y - 1LL * a.y * b.x;
    return cross == 0;
}

int sweep(int n, int colorAbove) {
    int colorBelow = 1 - colorAbove;
    
    for (int i = 0; i < n; ++i){
        assert(v[i].x != 0 or v[i].y != 0);
    }
    sort(v, v + n, compare);

    int score = 0;
    for (int i = 0; i < n; ++i) {
        if (above(v[i]) and v[i].color != colorAbove) score += v[i].value;
        if (below(v[i]) and v[i].color != colorBelow) score += v[i].value;
    }
    
    // printf("Will begin sweeping. Initial score = %d\n", score);
    // printf("Points are: "); for (int i = 0; i < v.size(); ++i) printf("(%d, %d) ", v[i].x, v[i].y); puts("");

    int ans = score;

    for (int i = 0, j; i < n; i = j) {
        j = i;
        while (j < n and equal(v[j], v[i])) {
            // process j
            if (above(v[j])) {
                if (v[j].color == colorAbove) score += v[j].value; // I found a blue point above
                else score -= v[j].value;
            }
            if (below(v[j]) ) {
                if (v[j].color == colorBelow) score += v[j].value;
                else score -= v[j].value;
            }
            j++;
        }
        if (score < ans) ans = score;
    }
    return ans;
}

int main(){
    int P, L;
    while (cin >> P >> L) {
        if (P == 0 and L == 0) break;
        for (int i = 0; i < P; ++i) {
            cin >> trees[i].x >> trees[i].y >> trees[i].value;
            trees[i].color = 0;
        }
        for (int i = 0; i < L; ++i) {
            cin >> trees[P + i].x >> trees[P + i].y >> trees[P + i].value;
            trees[P + i].color = 1;
        }
        int n = P + L;
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                if (trees[i].x == trees[j].x and trees[i].y == trees[j].y) {
                    puts("Two trees are equal!");
                    return 0;
                }
            }
        }

        int ans = 1 << 30;
        for (int i = 0; i < n; ++i) {
            const Tree &pivot = trees[i];
            int m = 0;
            for (int j = 0; j < n; ++j) if (i != j) {
                v[m].x = trees[j].x - pivot.x;
                v[m].y = trees[j].y - pivot.y;
                v[m].color = trees[j].color;
                v[m].value = trees[j].value;
                m++;
            }
            assert(m == n - 1);
            ans = min(ans, sweep(m, 0));
            ans = min(ans, sweep(m, 1));
        }
        cout << ans << endl;
    }
    
    return 0;
}