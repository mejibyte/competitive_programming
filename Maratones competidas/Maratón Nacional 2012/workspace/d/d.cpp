using namespace std;
# include <algorithm>
# include <iostream>
# include <iterator>
# include <sstream>
# include <fstream>
# include <cassert>
# include <cstdlib>
# include <string>
# include <cstring>
# include <cstdio>
# include <vector>
# include <cmath>
# include <queue>
# include <stack>
# include <map>
# include <set>

#define For(i, a, b) for (int i = (a); i < (b); i++)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != v.end(); x++)
#define D(x) cout << #x  " = " << (x) << endl

const double EPS = 1e-9;
int cmp (double x, double y = 0, double tol = EPS){
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

map<int, long long> memo;

// Retorna la suma de todos los digitos de los numeros [1, bound], inclusive.
long long f(int bound) {
    if (bound < 10) {
        long long ans = 0;
        for (int i = 0; i <= bound; ++i) ans += i;
        return ans;
    }
    if (memo.count(bound)) return memo[bound];
    
    int len = 0;
    int x = bound;
    while (x > 0) x /= 10, len++;
    
    long long pow = 1;
    for (int i = 0; i < len; ++i) pow *= 10;
    // pow == 10 ** len
    
    int first_digit = bound / (pow / 10);
    assert(first_digit < 10);
    
    long long ans = 0;
    for (long long d = 1; d < first_digit; ++d) {
        ans += d * (pow / 10);
        ans += f(pow / 10 - 1);
    }
    
    int rest = bound - first_digit * (pow / 10);
    ans += 1LL * first_digit * (rest + 1);
    ans += f(rest);
    ans += f(pow / 10 - 1);
    
    return memo[bound] = ans;
    
}

int main () {
    freopen("digsum.in", "r", stdin);
    
    int low, high;
    while (cin >> low >> high) {
        if (low == 0 and high == 0) break;
        long long ans = f(high);
        if (low - 1 > 0) ans -= f(low - 1);
        cout << ans << endl;
    }
    
    return 0;
}
