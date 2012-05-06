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

const int mod = 1000000007;

// Assumes gcd(a, n) == 1 and a > 0.
// Returns v such that a * v == 1 (mod n).
long long mod_inverse(long long a, long long n) {
    long long i = n, v = 0, d = 1;
    while (a > 0) {
        long long t = i / a, x = a;
        a = i % x;
        i = x;
        x = d;
        d = v - t * x;
        v = x;
    }
    v %= n;
    if (v < 0) v += n;
    return v;
}

int main(){
    int n;
    while (cin >> n) {
        long long ans = 1;
    
        for (int i = 1; i <= 2*n; ++i){
            ans *= i;
            ans %= mod;
        }
    
        long long d = 1;
        for (int i = 1; i <= n; ++i) {
            d *= i;
            d %= mod;
            d *= i;
            d %= mod;
        }
        d *= (n + 1);
        d %= mod;
    
        ans *= mod_inverse(d, mod);
        ans %= mod;
    
        cout << n << "->";
        cout << ans << endl;
    }
    return 0;
}