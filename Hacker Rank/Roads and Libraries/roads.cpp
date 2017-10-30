// Andrés Mejía
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
using namespace std;

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cerr << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

const int MAXN = 100005;


// Disjoint-set forests from Cormen 21.3.
int p[MAXN];

int find(int u) {
    return u == p[u] ? u : p[u] = find(p[u]);
}

void join(int u, int v) {
    p[find(u)] = find(v);
}

int main() {
    int q;
    cin >> q;
    for(int a0 = 0; a0 < q; a0++){
        int n;
        int m;
        long long cost_library, cost_road;
        cin >> n >> m >> cost_library >> cost_road;

        // Init.
        for (int i = 0; i < n; ++i) {
            p[i] = i;
        }

        int need_edges = 0;
        for (int a1 = 0; a1 < m; a1++){
            int a, b;
            cin >> a >> b;
            a--, b--;

            if (find(a) != find(b)) {
                join(a, b);
                need_edges++;
            }
        }

        long long answer = need_edges * cost_road;
        for (int i = 0; i < n; ++i) {
            if (find(i) == i) {
                answer += cost_library;
            }
        }


        cout << min(n * cost_library, answer) << endl;
    }
    return 0;
}
