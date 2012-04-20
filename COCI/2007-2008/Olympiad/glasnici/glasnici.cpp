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

const int MAXN = 1000005;
double a[MAXN];

int main(){
    double k; int n;
    cin >> k >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    double length = a[n - 1] - a[0];
    if (cmp(length, k) <= 0) {
        puts("0.000\n");
    } else {
        double c = (a[0] + a[n - 1]) / 2.0;
        double start = c - (n - 1) * k / 2.0;
        double ans = 0.0;
        for (int i = 0; i < n; ++i) {
            double take = abs(a[i] - (start + i * k));
            ans = max(ans, take);
        }
        printf("%.10lf\n", ans);
    }
    return 0;
}