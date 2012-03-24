// Andrés Mejía

// Accepted, 10.260s

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

Tree trees[MAXN];
int v[MAXN];

inline bool above(const Tree &t) {
    if (t.x == 0 and t.y == 0) printf("t = (%d, %d)\n", t.x, t.y);
    assert(t.x != 0 or t.y != 0);
    if (t.y == 0) return t.x > 0;
    return t.y > 0;
}

inline bool below(const Tree &t) {
    return !above(t);
}


bool compare(int a, int b) {
    long long cross = 1LL * trees[a].x * trees[b].y - 1LL * trees[a].y * trees[b].x;
    if (!above(trees[a])) cross = -cross;
    if (!above(trees[b])) cross = -cross;
    return cross > 0;
}

bool equal(int a, int b) {
    long long cross = 1LL * trees[a].x * trees[b].y - 1LL * trees[a].y * trees[b].x;
    return cross == 0;
}

int sweep(int n, int colorAbove) {
    int colorBelow = 1 - colorAbove;
    sort(v, v + n, compare);

    int score = 0;
    for (int i = 0; i < n; ++i) {
        const Tree &t = trees[v[i]];
        if (above(t) and t.color != colorAbove) score += t.value;
        if (below(t) and t.color != colorBelow) score += t.value;
    }
    
    // printf("Will begin sweeping. Initial score = %d\n", score);
    // printf("Points are: "); for (int i = 0; i < v.size(); ++i) printf("(%d, %d) ", v[i].x, v[i].y); puts("");

    int ans = score;

    for (int i = 0, j; i < n; i = j) {
        j = i;
        while (j < n and equal(v[j], v[i])) {
            const Tree &t = trees[v[j]];
            // process j
            if (above(t)) {
                if (t.color == colorAbove) score += t.value; // I found a blue point above
                else score -= t.value;
            }
            if (below(t) ) {
                if (t.color == colorBelow) score += t.value;
                else score -= t.value;
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
                v[m++] = j;
                trees[j].x -= pivot.x;
                trees[j].y -= pivot.y;
            }
            assert(m == n - 1);
            ans = min(ans, sweep(m, 0));
            ans = min(ans, sweep(m, 1));
            for (int j = 0; j < n; ++j) if (i != j) {
                v[m] = j;
                trees[j].x += pivot.x;
                trees[j].y += pivot.y;
            }
        }
        cout << ans << endl;
    }
    
    return 0;
}