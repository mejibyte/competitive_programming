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

const int MAXN = 105;
int d[MAXN];
int l[MAXN];
int n, true_love;

int memo[MAXN][MAXN];

bool can_reach(int at, int prev) {
    assert(1 <= at and at <= n);
    assert(0 <= prev and prev < n);
    
    int len = min(l[at], d[at] - d[prev]);

    // reach immediately
    if (d[at] + len >= true_love) {
        return true;
    }
    
    if (memo[at][prev] != -1) return memo[at][prev];
    bool ans = false;
    for (int next = at + 1; next <= n; ++next) {
        if (d[at] + len >= d[next]) {
            if (can_reach(next, at)) {
                ans = true;
                break;
            }
        }
    }
    return memo[at][prev] = ans;
}

void solve(){
    cin >> n;

    d[0] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> d[i] >> l[i];
    }
    cin >> true_love;
    memset(memo, -1, sizeof memo);
    bool ans = can_reach(1, 0);
    printf("%s\n", ans ? "YES" : "NO");
}

int main(){
    int T; cin >> T;
    for (int i = 1; i <= T; ++i) {
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}