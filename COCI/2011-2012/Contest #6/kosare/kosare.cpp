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

const int MAXN = 105, MAXT = 15, mod = 1000000007;
int dp[MAXN][1 << MAXT];
int box[MAXN];

int main(){
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int k; cin >> k;
        box[i] = 0;
        while (k--) {
            int toy; cin >> toy; toy--;
            box[i] |= (1 << toy);
        }
    }
    for (int j = 0; j < (1 << m); ++j) dp[n][j] = 0;
    dp[n][0] = 1;
    
    for (int i = n; i >= 1; --i) {
        for (int j = 0; j < (1 << m); ++j) {
            if (dp[i][j] == 0) continue;
            (dp[i - 1][j] += dp[i][j]) %= mod;
            (dp[i - 1][j | box[i - 1]] += dp[i][j]) %= mod;
        }
    }

    cout << dp[0][(1 << m) - 1] << endl;
    return 0;   
}