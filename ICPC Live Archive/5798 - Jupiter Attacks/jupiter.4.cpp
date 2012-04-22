// Andrés Mejía

// Accepted. Uses a Segment Tree instead a Fenwick Tree.

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

const int MAXN = 100005;

int N, B, P;

int power[MAXN]; // power[i] = B^i (mod P)

namespace Tree {
    int tree[1 << 18];
    
    void clear(int u, int l, int r) {
        tree[u] = 0;
        if (l < r) {
            int m = (l + r) / 2;
            clear(2*u + 1, l, m);
            clear(2*u + 2, m + 1, r);
        }
    }
    
    int update(int u, int l, int r,   int at, int what) {
        if (at < l or at > r) return tree[u];
        if (l == at and r == at) return tree[u] = what % P;
        assert(l < r);
        int m = (l + r) / 2;
        int left = update(2*u + 1, l, m,  at, what);
        int right = update(2*u + 2, m + 1, r, at, what);
        return tree[u] = (1LL * right + 1LL * left * power[r - m]) % P;
    }
    
    int query(int u, int l, int r, int p, int q) {
        if (q < l or p > r) return 0;
        p = max(l, p);
        q = min(r, q);
        if (p <= l and r <= q) return tree[u];
        assert(l < r);
        int m = (l + r) / 2;
        int left = query(2*u + 1, l, m, p, q);
        int right = query(2* u + 2, m + 1, r, p, q);
        return (1LL * right + 1LL * left * power[max(q - m, 0)]) % P;
    }
    
    // For debugging
    void print(int u, int l, int r) {
        printf("tree[%d, %d] = %d\n", l, r, tree[u]);
        if (l < r) {
            int m = (l + r) / 2;
            print(2*u + 1, l, m);
            print(2*u + 2, m + 1, r);
        }
    }
};


inline int mod(int a) {
    return ((a % P) + P) % P;
}

int main(){
    int queries;
    while (scanf(" %d %d %d %d ", &B, &P, &N, &queries) == 4) {
        if (B == 0 and P == 0 and N == 0 and queries == 0) break;
        power[0] = 1;
        for (int i = 1; i <= N + 1; ++i) {
            power[i] = (1LL * power[i - 1] * B) % P;
        }
        
        Tree::clear(0, 1, N);
        
        while (queries--) {
            char type;
            int u, v;
            scanf(" %c %d %d ", &type, &u, &v);
            if (type == 'E') {
                // change item at position u with v
                Tree::update(0, 1, N, u, v);
            } else {
                // get hash for [u, v]
                int ans = Tree::query(0, 1, N, u, v);
                printf("%d\n", ans);
            }
        }
        // Debug tree
        // for (int i = 1; i <= N; ++i){
        //     printf("h(%d, %d) = %d\n", i, i, Tree::query(0, 1, N, i, i));
        // }
        // Tree::print(0, 1, N);
        
        puts("-");
    }
    return 0;
}