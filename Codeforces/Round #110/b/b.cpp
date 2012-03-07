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

int main(){
    int n; cin >> n;
    vector< int > r(n);
    for (int i = 0; i < n; ++i) cin >> r[i];
    sort(r.rbegin(), r.rend());
    
    const double pi = 2 * acos(0);
    double ans = 0.0;
    for (int i = 0; i < n; ++i) {
        int sign = (i % 2 == 0) ? +1 : -1;
        ans += pi * r[i] * r[i] * sign;
    }
    printf("%.15lf\n", ans);
    return 0;
}