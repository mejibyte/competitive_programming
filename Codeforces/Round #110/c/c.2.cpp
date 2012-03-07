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

const int MAXN = 2005;
int dp[MAXN][MAXN];

int main(){
    string s, t;
    cin >> s >> t;
    
    int n = s.size();
    int m = t.size();
    
    for (int i = 0; i < n; ++i) {
        dp[i][0] = (s[i] != t[0]);
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            dp[i][j] = dp[i][j - 1] + 1;
            if (i - 1 >= 0) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + (s[i] != t[j]) );
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
            }
        }
    }
    int ans = (1 << 30);
    for (int i = 0; i < n; ++i) {
        int option = dp[i][m - 1];
        ans = min(ans, option);
    }

    cout << ans << endl;
    return 0;
}