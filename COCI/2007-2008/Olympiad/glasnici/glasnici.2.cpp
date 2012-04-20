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
double a[MAXN], k;
int n;

bool works(double run) {
    double at = a[0] + run;
    for (int i = 1; i < n; ++i) {
        // run to the left
        if (at + k + EPS < a[i] - run) return false;
        
        double next = a[i] + run;
        if (cmp(next - at, k) > 0) {
            next = at + k;
        }
        
        at = next;
    }
    return true;
}

int main(){
    cin >> k >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    double length = a[n - 1] - a[0];
    if (cmp(length, k) <= 0) {
        puts("0.000\n");
    } else {
        double low = 0, high = length + 1;
        for (int i = 0; i < 200; ++i) {
            double m = (low + high) / 2;
            if (works(m)) {
                high = m;
            } else {
                low = m;
            }
        }
        printf("%.10lf\n", low);
    }
    return 0;
}