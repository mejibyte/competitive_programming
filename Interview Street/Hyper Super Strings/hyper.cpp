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

set<string> dict;
map<string, bool> cache;

bool can_split(const string &s) {
    if (s == "") return true;
    if (cache.count(s) > 0) return cache[s];
    for (int i = 1; i < s.size(); ++i) {
        string left = s.substr(0, i);
        string right = s.substr(i);
        if (dict.count(left) > 0 and (dict.count(right) > 0 or can_split(right)) ) {
            return cache[s] = true;
        }
    }
    return cache[s] = false;
}

int main(){
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        dict.insert(s);
    }
    vector<string> coins;
    for (set<string>::iterator i = dict.begin(); i != dict.end(); ++i) {
        
        if (!can_split(*i)) {
            coins.push_back(*i);
        }
    }

    const int mod = 1000000007;
    vector<int> dp(m + 1, 0);
    dp[0] = 1;
    for (int i = 0; i <= m; ++i) {
        if (dp[i] == 0) continue;
        
        for (int k = 0; k < coins.size(); ++k) {
            int len = coins[k].size();
            if (i + len <= m) {
                (dp[i + len] += dp[i]) %= mod;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= m; ++i) {
        (ans += dp[i]) %= mod;
    }
    cout << ans << endl;
    return 0;
}