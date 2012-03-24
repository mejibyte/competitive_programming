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

const int MAXN = 100005;

int c[MAXN], F;

// Returns how many ways you can pack the candies if each pack has s candies.
long long pack(long long s, long long sum) {
    if (s < 2) return 0;
    assert(s % F == 0);
    if (sum % s != 0) return 0;
    long long mod = (c[0] - s - s / F) % s;
    long long smallest = (1LL << 60);
    for (int i = 0; i < F; ++i) {
        long long r = c[i] - s - s / F;
        if (r < 0 or r % s != mod) return 0;
        if (r < smallest) smallest = r;
    }
    return smallest / s + 1;
}

// Returns the answer for this test case.
// sum is the total number of candies and g is the gcd of
// all c[i]'s.
long long solve(long long sum, int g) {
    if (sum % F != 0) return 0;
    long long ans = 0;
    for (long long d = 1; d * d <= g; ++d) {
        if (g % d != 0) continue;
        ans += pack(d * F, sum);
        if (g / d != d) ans += pack(g / d * F, sum);
    }
    return ans;
}

int main(){
    while (scanf("%d", &F) == 1 and F > 0) {
        int g = 0;
        long long sum = 0;
        for (int i = 0; i < F; ++i) {
            scanf("%d", c + i);
            g = __gcd(g, c[i]);
            sum += c[i];
        }
        printf("%lld\n", solve(sum, g));
    }
    return 0;
}