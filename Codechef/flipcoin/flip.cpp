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

int size[1 << 18];
bool pending[1 << 18];

void propagate(int u, int l, int r) {
    if (pending[u]) {
        size[u] = r - l + 1 - size[u];
        if (l < r) {
            pending[2*u+1] ^= 1;
            pending[2*u+2] ^= 1;
        }
        pending[u] = false;
    }
}

void toggle(int u, int l, int r, int p, int q) {
    propagate(u, l, r);
    if (q < l or p > r) return; // outside
    if (p <= l and r <= q) {
        pending[u] ^= 1;
        propagate(u, l, r);
        return;
    }
    int m = (l + r) / 2;
    toggle(2*u+1, l, m, p, q);
    toggle(2*u+2, m+1, r, p, q);
    
    size[u] = size[2*u+1] + size[2*u+2];
}

int get(int u, int l, int r, int p, int q) {
    propagate(u, l, r);
    if (q < l or p > r) return 0;
    if (p <= l and r <= q) {
        return size[u];
    }
    int m = (l + r) / 2;
    return get(2*u+1, l, m, p, q) + get(2*u+2, m+1, r, p, q);
}

int main(){
    ios::sync_with_stdio(false);
    
    int n, q;
    cin >> n >> q;
    while (q--) {
        int type, u, v;
        cin >> type >> u >> v;
        assert(u <= v);
        
        if (type == 0) {
            toggle(0, 0, n - 1, u, v);
        } else {
            cout << get(0, 0, n - 1, u, v) << endl;
        }
    }
    
    return 0;
}