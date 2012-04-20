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

const int MAXN = 1000005, MAXT = 20, mod = 1000000007;
int dp[1 << MAXT], power[MAXN];

int main(){
    ios::sync_with_stdio(false);
    
    int n, m;
    cin >> n >> m;
    int full = (1 << m) - 1;
    
    for (int i = 0; i < n; ++i) {
        int k; cin >> k;
        int box = 0;
        while (k--) {
            int toy; cin >> toy; toy--;
            box |= (1 << toy);
        }
        dp[ full ^ box ]++;
    }

    // dp[mask] = How many boxes are there such that they don't contain any of the toys indicated in mask.
    // dp[mask] = Cuántas cajas hay tal que no incluyan ninguno de los juguetes indicados en mask.
    for (int bit = 0; bit < m; ++bit) {
        for (int mask = 0; mask <= full; ++mask) {
            if (mask & (1 << bit)) {
                dp[ mask ^ (1 << bit) ] += dp[mask];
            }
        }
    }
    assert(dp[0] == n);

    // precompute powers of 2
    power[0] = 1;
    for (int i = 1; i <= n; ++i) {
        power[i] = 2 * power[i - 1];
        power[i] %= mod;
    }
    
    // Use inclusion-exclusion principle to count all subsets of boxes that include all toys:
    // This number is 2^n - (# of subsets that don't include 1 toy) + (# of subsets that don't include 2 toys) - (# of subsets that don't include 3 toys) + ... + (-1)^n(# of subsets that don't include n toys).
    
    int ans = 0;
    for (int mask = 0; mask <= full; ++mask) {
        assert(0 <= dp[mask] and dp[mask] <= n);
        int not_having_mask = power[ dp[mask] ]; // number of subsets that don't include the toys indicated in mask.
        if (__builtin_popcount(mask) % 2 == 0) {
            ans += not_having_mask;
        } else {
            ans -= not_having_mask;
        }
        if (ans >= mod) ans -= mod;
        if (ans < 0) ans += mod;
    }
    cout << ans << endl;
    return 0;
}