// Andrés Mejía

// Accepted

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

const int MAXN = 1005;

int balls[MAXN][MAXN];
long long dp[MAXN][MAXN];
long long above[MAXN][MAXN];

int main(){
    int n;
    while (scanf("%d", &n) == 1 and n > 0) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= i; ++j) scanf("%d", &balls[i][j]);
        }

        for (int j = 0; j < n; ++j) {
            above[j][j] = balls[j][j];
            for (int i = j + 1; i < n; ++i) {
                above[i][j] = balls[i][j] + above[i - 1][j];
            }
        }

        dp[n][n - 1] = 0;
        for (int j = n - 1; j >= 0; --j) {
            for (int i = j; i < n; ++i) {
                dp[i][j] = 0;
                if (i - 1 >= j) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j]);
                }
                long long score = above[i][j] + dp[min(n - 1, i + 1)][j + 1];
                dp[i][j] = max(dp[i][j], score);
            }
        }
        printf("%lld\n", dp[n - 1][0]);
    }
    return 0;
}