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

map< pair<int, int>, bool > memo;

bool can_reach(int at, int len) {
    if (at == n) {
        return d[at] + len >= true_love;
    }
    pair<int, int> key = make_pair(at, len);
    if (memo.count(key) > 0) return memo[key];
    
    bool ans = false;
    for (int next = at + 1; next <= n; ++next) {
        if (d[at] + len >= d[next]) {
            int nlen = min(d[next] - d[at], l[next]);
            if (can_reach(next, nlen)) {
                ans = true;
                break;
            }
        }
    }
    return memo[key] = ans;
}

void solve(){
    cin >> n;

    d[0] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> d[i] >> l[i];
    }
    cin >> true_love;
    memo.clear();
    bool ans = can_reach(1, d[1]);
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