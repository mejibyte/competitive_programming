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

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

// Returns ceil(a / b)
long long myCeil(long long a, long long b) {
    if (a < 0 and b < 0) return myCeil(-a, -b);
    if (a > 0 and b > 0) return (a + b - 1) / b;
    // only one is negative negative
    return a / b;
}

int main(){
    int t1, t2, x1, x2, t0;
    while (cin >> t1 >> t2 >> x1 >> x2 >> t0) {
        if  (t1 == t2) { // special case
            printf("%d %d\n", x1, x2); // open both at maximum
            continue;
        }
        
        assert(t2 >= t0);
        long double bestDistance = t2 - t0;
        pair<int, int> ans(0, x2);
        
        if (t1 >= t0 and cmp(t1 - t0, bestDistance) < 0) { // better option
            bestDistance = t1 - t0;
            ans = make_pair(x1, 0);
        }
        
        if (t2 > t0) { // if they are equal it was handled above
            for (int y1 = 1; y1 <= x1; ++y1) {
                long long c = 1LL * y1 * (t0 - t1);
                long long y2 = myCeil(c, t2 - t0);
                if (y2 == 0) continue;
                long double option = (0.0L + 1LL * t1 * y1 + 1LL * t2 * y2) / (y1 + y2);
                assert(cmp(option, t0) >= 0);
                option -= t0;
                if (y2 <= x2 and cmp(option, bestDistance) <= 0) {
                    bestDistance = option;
                    ans = make_pair(y1, y2);
                }
            }
        }
        printf("%d %d\n", ans.first, ans.second);
    }
    return 0;
}