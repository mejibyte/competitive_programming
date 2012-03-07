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

const int MAXS = 2001;

int dp[350][MAXS + 5];
int choice[350][MAXS + 5];

int main(){
    vector< Pyramid > p;
    for (int i = 2, s = 1; ; ++i) {
        s += i * i;
        if (s >= MAXS) break;
        p.push_back( Pyramid(i, s, true) );
    }
    for (int i = 3, s = 1; ; i += 2) {
        s += i * i;
        if (s >= MAXS) break;
        p.push_back( Pyramid(i, s, false) );
    }
    for (int i = 4, s = 4; ; i += 2) {
        s += i * i;
        if (s >= MAXS) break;
        p.push_back( Pyramid(i, s, false) );
    }
    sort(p.begin(), p.end());
    reverse(p.begin(), p.end());
 
    // for (int i = 0; i <= 12; ++i) {
    //     printf("%d%c = %d\n", p[i].base, p[i].high ? 'H' : 'L', p[i].cubes);
    // }
    for (int i = 0; i + 1 < p.size(); ++i) {
         assert(p[i].cubes != p[i + 1].cubes);
    }

    memset(dp, 0x7F, sizeof dp);
    dp[0][0] = 0;
    for (int i = 1; i <= p.size(); ++i) {
        int value = p[i - 1].cubes;
        assert( value < MAXS );
        for (int j = 0; j < MAXS; ++j) {
            dp[i][j] = dp[i - 1][j];
            choice[i][j] = 0;
            if (j - value >= 0 and dp[i - 1][j - value] + 1 <= dp[i][j]) {
                dp[i][j] = dp[i - 1][j - value] + 1;
                choice[i][j] = 1;
            }
        }
    }

    for (int run = 1; ; ++run) {
        int n; scanf("%d", &n);
        if (n == 0) break;
        printf("Case %d: ", run);
        if (n >= MAXS) {
            puts("Too big for me.");
            continue;
        }
        
        if (dp[p.size()][n] > p.size()) {
            puts("impossible");
            continue;
        }


        vector< Pyramid > ans;
        for (int i = p.size(), j = n; i > 0; --i) {
            if (choice[i][j] == 1) {
                ans.push_back( p[i - 1] );
                j -= ans.back().cubes;
            }
        }
        sort(ans.begin(), ans.end());
        for (int i = 0; i < ans.size(); ++i) {
            if (i > 0) printf(" ");
            printf("%d%c", ans[i].base, ans[i].high ? 'H' : 'L');
        }
        puts("");

    }

    return 0;
}