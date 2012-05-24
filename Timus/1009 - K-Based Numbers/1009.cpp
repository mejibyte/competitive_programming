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

long long dp[20][10];

int main(){
    int n, k; cin >> n >> k;

    dp[1][0] = 0;
    for (int first = 1; first < k; ++first) dp[1][first] = 1;
    
    for (int len = 1; len < n; ++len) {
        for (int last = 0; last < k; ++last) {
            if (dp[len][last] > 0) {
                for (int next = 0; next < k; ++next) {
                    if (last == 0 and next == 0) continue;
                    dp[len + 1][next] += dp[len][last];
                }
            }
        }
    }
    
    long long ans = 0;
    for (int last = 0; last < k; ++last) ans += dp[n][last];
    cout << ans << endl;
    
    return 0;
}