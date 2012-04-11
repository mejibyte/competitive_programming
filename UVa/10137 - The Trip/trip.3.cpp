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

const int MAXN = 1005;
int v[MAXN];

int main(){
    int n;
    while (scanf("%d", &n) == 1) {
        if (n == 0) break;
        int total = 0;
        for (int i = 0; i < n; ++i) {
            int x, y;
            scanf("%d.%d", &x, &y);
            v[i] = 100 * x + y;
            assert(v[i] >= 0);
            total += v[i];
        }
        
        int split = total / n; // floor(total / n)
        int splat = (total + n - 1) / n; // ceil(total / n)
        
        int below = 0, above = 0;
        for (int i = 0; i < n; ++i) {
            if (v[i] < split) below += split - v[i];
            else if (v[i] > splat) above += v[i] - splat;
        }
        int ans = max(below, above);
        printf("$%d.%.2d\n", ans / 100, ans % 100);
    }
    return 0;
}