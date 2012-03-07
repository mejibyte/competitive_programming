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

struct Pyramid {
    int base, cubes;
    bool high;
    
    Pyramid(int base, int cubes, bool high) : base(base), cubes(cubes), high(high) {}
    Pyramid(){}
    bool operator < (const Pyramid &p) const {
        if (cubes != p.cubes) return cubes > p.cubes;
        return high > p.high;
    }
};

const int MAXS = 1000005;

bool been[MAXS + 5];
int took[MAXS + 5];

int main(){
    vector< Pyramid > p;
    for (int i = 2, s = 1; ; ++i) {
        s += i * i;
        if (s > MAXS) break;
        p.push_back( Pyramid(i, s, true) );
    }
    for (int i = 3, s = 1; ; i += 2) {
        s += i * i;
        if (s > MAXS) break;
        p.push_back( Pyramid(i, s, false) );
    }
    for (int i = 4, s = 4; ; i += 2) {
        s += i * i;
        if (s > MAXS) break;
        p.push_back( Pyramid(i, s, false) );
    }
    sort(p.begin(), p.end());
    // for (int i = p.size() - 1; i >= p.size() - 12; --i) {
    //     printf("%d%c = %d\n", p[i].base, p[i].high ? 'H' : 'L', p[i].cubes);
    // }
    for (int i = 0; i + 1 < p.size(); ++i) {
        assert( p[i].cubes != p[i + 1].cubes );
    }
    
    queue< int > q;
    been[0] = true;
    took[0] = -1;
    q.push( 0 );
    while (q.size() > 0) {
        int u = q.front(); q.pop();
        #define debug ((u == 84 || u == 119 || u == 133 || u == 148))
        if debug printf("popped %d with took = %d\n", u, took[u]);
        for (int k = took[u] + 1; k < p.size(); ++k) {
            int next = u + p[k].cubes;
            if (next >= MAXS) continue;
            if (been[next]) continue;
            
            if debug printf("   can go to %d with k = %d (p[k].cubes = %d)\n", next, k, p[k].cubes);
            took[next] = k;
            if debug printf("    assigned took[next=%d] = %d\n", next, took[next]);
            been[next] = true;
            q.push( next );
        }
    }

    for (int run = 1; ; ++run) {
        int n; scanf("%d", &n);
        if (n == 0) break;
        printf("Case %d: ", run);
        if (!been[n]) {
            puts("impossible");
            continue;
        }
        vector< Pyramid > ans;
        while (n > 0) {
            ans.push_back( p[ took[n] ]);
            n -= p[ took[n] ].cubes;
        }
        reverse(ans.begin(), ans.end());
        for (int i = 0; i + 1 < ans.size(); ++i) {
            assert(ans[i] < ans[i + 1]);
        }
        for (int i = 0; i < ans.size(); ++i) {
            if (i > 0) printf(" ");
            printf("%d%c", ans[i].base, ans[i].high ? 'H' : 'L');
        }
        puts("");
    }
    
    return 0;
}