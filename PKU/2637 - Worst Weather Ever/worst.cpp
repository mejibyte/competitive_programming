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

const int MAXN = 50005;

int year[MAXN], rain[MAXN];

namespace SegmentTree {
    int tree[1 << 17]; // 2^16 is the first power of 2 >= 50000. We need twice that.
    
    int init(int u, int l, int r) {
        if (l == r) return tree[u] = rain[l];
        int m = (l + r) / 2;
        return tree[u] = max(init(2*u + 1, l, m), init(2*u + 2, m + 1, r));
    }

    int query(int u, int l, int r,    int p, int q) {
        if (q < l or r < p) return INT_MIN;
        if (p <= l and r <= q) return tree[u];
        int m = (l + r) / 2;
        return max(query(2*u + 1, l, m, p, q), query(2*u + 2, m + 1, r, p, q));
    }
}


void solve(int from, int to, int n) {
    bool know_from = binary_search(year, year + n, from);
    bool know_to = binary_search(year, year + n, to);
    
    if (!know_from and !know_to) {
        puts("maybe");
        return;
    }
    
    // aquí sé uno de los dos
    int a = lower_bound(year, year + n, from) - year;
    int b = lower_bound(year, year + n, to) - year;
    if (know_from and know_to) {
        if (rain[b] > rain[a]) { // it rained more today than before
            puts("false");
            return;
        }
    }
    
    // sé uno o los dos
    int least = know_to ? rain[b] : rain[a];
    
    int p = upper_bound(year, year + n, from) - year;
    int q = lower_bound(year, year + n, to) - year - 1;
    assert(p >= 0 and q >= 0);
    if (p <= q and SegmentTree::query(0, 0, n - 1, p, q) >= least) {
        puts("false");
        return;
    }
    
    // now it's either valid or maybe
    if (!know_from or !know_to or b - a != to - from) { // some years missing
        puts("maybe");
        return;
    }
    
    puts("true");
}

int main(){
    int n;
    bool first = true;
    while (scanf("%d", &n) == 1 and n > 0) {
        if (!first) puts(""); first = false;
        
        for (int i = 0; i < n; ++i) scanf("%d %d", &year[i], &rain[i]);
        
        SegmentTree::init(0, 0, n - 1);
        
        int queries; scanf("%d", &queries);
        for (int q = 0; q < queries; ++q) {
            int from, to; scanf("%d %d", &from, &to);
            solve(from, to, n);
        }
        
    }
    return 0;
}