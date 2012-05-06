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

const int MAXN = 1005;

bool g[MAXN][MAXN];

void solve() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char c; cin >> c;
            g[i][j] = (c == '1');
        }
    }
        
    static int p[MAXN];
    for (int i = 0; i < n; ++i) {
        p[i] = i;
    }
    
    do {
        bool valid = true;
        for (int i = 0; i + 1 < n and valid; ++i) {
            valid &= g[p[i]][p[i + 1]];
        }
        if (valid) {
            printf("Yes");
            for (int i = 0; i < n; ++i) printf(" %d", p[i]);
            puts("");
            return;
        }
    } while (next_permutation(p, p + n));
    puts("No");
}


int main(){
    int T; cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}