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

const int MAXN = 10005;
int d[MAXN];
int l[MAXN];
int n, true_love;

int dp[MAXN];

void solve(){
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> d[i] >> l[i];
        dp[i] = 0;
    }
    cin >> true_love;
    
    dp[0] = min(d[0], l[0]);
    
    for (int i = 0; i < n; ++i) {
        int len = dp[i];
        if (len == 0) continue;
        for (int j = i + 1; j < n; ++j) {
            if (d[i] + len >= d[j]) {
                int new_len = min(d[j] - d[i], l[j]);
                dp[j] = max(dp[j], new_len);
            } else {
                break;
            }
        }
    }

    bool ans = false;
    for (int i = 0; i < n; ++i) {
        if (d[i] + dp[i] >= true_love) {
            ans = true;
            break;
        }
    }
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