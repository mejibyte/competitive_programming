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

typedef long long Int;

const int MAXN = 1005;
Int tax[MAXN], origin[MAXN], destiny[MAXN];


void solve(int n) {
    string start, end; cin >> start >> end;
    for (int i = 0; i < n; ++i) cin >> tax[i];
    
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (tax[i] < tax[j]) { // sort from greater to smaller
                swap(tax[i], tax[j]);
                swap(start[i], start[j]);
                swap(end[i], end[j]);
            }
        }
    }
    

    origin[n] = destiny[n] = 0;
    for (int i = n - 1; i >= 0; --i) {
        origin[i] = (start[i] - '0') * tax[i];
        if (i + 1 < n) origin[i] += origin[i + 1];
        
        destiny[i] = (end[i] - '0') * tax[i];
        if (i + 1 < n) destiny[i] += destiny[i + 1];
    }
    
    static long long dp[MAXN][2*MAXN];
    const long long oo = (1LL << 61);
    
    static bool all_equal[MAXN];
    all_equal[n] = true;
    for (int i = n - 1; i >= 0; --i) {
        all_equal[i] = all_equal[i + 1] and start[i] == end[i];
    }
    
    for (int i = n; i >= 0; --i) {
        for (int t = 0; t <= 2*n; ++t) {
            
            if (i == n) {
                dp[i][t] = 0;
            } else if (t == 0) {
                dp[i][t] = oo;
                if (all_equal[i]) dp[i][t] = 0;
            } else {
                assert(i < n);
                if (start[i] == '0' and end[i] == '0') {
                    dp[i][t] = dp[i + 1][t];
                } else if (start[i] == '0' and end[i] == '1') {
                    dp[i][t] = dp[i + 1][t - 1] + destiny[i];
                } else if (start[i] == '1' and end[i] == '0') {
                    dp[i][t] = origin[i + 1] + dp[i + 1][t - 1];
                } else if (start[i] == '1' and end[i] == '1') {
                    dp[i][t] = 1LL * t * tax[i] + dp[i + 1][t];
                    if (t - 2 >= 0) dp[i][t] = min(dp[i][t], origin[i + 1] + dp[i + 1][t - 2] + destiny[i]);
                    dp[i][t] = min(dp[i][t], oo);
                }
                if (all_equal[i]) dp[i][t] = 0;
            }
        }
    }
    long long ans = oo;
    for (int t = 0; t <= 2*n; ++t) {
        ans = min(ans, dp[0][t]);
    }
    
    // puts("");
    // for (int i = 0; i <= n; ++i) {
    //     for (int t = 0; t <= 2*n; ++t){
    //         if (dp[i][t] == oo) {
    //             printf("%3s ", "inf");
    //         } else {
    //             printf("%3lld ", dp[i][t]);
    //         }
    //     }
    //     puts("");
    // }
    cout << ans << endl;
}

int main(){
    int run = 1, n;
    while (cin >> n) {
        if (n == 0) break;
        printf("Case %d: ", run++);
        solve(n);
    }
    return 0;
}