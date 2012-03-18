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
bool isPalindrome[MAXN][MAXN];

int main(){
    string s; cin >> s;
    int n = s.size();
    for (int i = 0; i < n; ++i) {
        isPalindrome[i][i] = true;
    }
    for (int i = 0; i + 1 < n; ++i) {
        isPalindrome[i][i + 1] = (s[i] == s[i + 1]);
    }
    for (int len = 3; len <= n; ++len) {
        for (int i = 0; i + len - 1 < n; ++i) {
            isPalindrome[i][i + len - 1] = (s[i] == s[i + len - 1]) and isPalindrome[i + 1][i + len - 2];
        }
    }
    
    static long long dp[MAXN];
    dp[n] = 0;
    for (int i = n - 1; i >= 0; --i) {
        dp[i] = dp[i + 1];
        for (int j = i; j < n; ++j) dp[i] += isPalindrome[i][j];
    }
    
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (isPalindrome[i][j]) {
                ans += dp[j + 1];
            }
        }
    }
    cout << ans << endl;
    return 0;
}