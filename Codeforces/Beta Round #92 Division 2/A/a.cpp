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

int main(){
    int n, k;
    while (cin >> n >> k) {
        long double sum = 0;
        
        int x0, y0;
        cin >> x0 >> y0;
        for (int i = 1; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            sum += hypot(x - x0, y - y0);
            x0 = x, y0 = y;
        }
        printf("%.9lf\n", (double)(sum * k / 50));
    }
    return 0;
}