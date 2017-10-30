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

// Linked list representation of disjoint sets from Cormen 21.2.
// Overall complexity: O(n log n)

// Elements in k-th set.
vector<int> set_elements[MAXN];

// current_set[i] = set that node i belongs to.
int current_set[MAXN];

int find(int u) {
    return current_set[u];
}

void merge(int u, int v) {
    int set_u = find(u);
    int set_v = find(v);
    // merge u's set into v's
    for (int i = 0; i < set_elements[set_u].size(); ++i) {
        int w = set_elements[set_u][i];
        current_set[w] = set_v;
        set_elements[set_v].push_back(w);
    }
    set_elements[set_u].clear();
}

void join(int u, int v) {
    if (set_elements[find(u)].size() < set_elements[find(v)].size()) {
        merge(u, v);
    } else {
        merge(v, u);
    }
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
            set_elements[i].clear();
            set_elements[i].push_back(i);
            current_set[i] = i;
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
