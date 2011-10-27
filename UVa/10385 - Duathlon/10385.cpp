// Accepted. Ternary search.
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

const double eps = 1e-9;

const int MAXN = 20;
double running_speed[MAXN], biking_speed[MAXN];
int n;

double margin(double x, int t) {
    double me = x / running_speed[n - 1] + (t - x) / biking_speed[n - 1];
    double them = 1e100;
    for (int i = 0; i < n - 1; ++i) {
        them = min(them,  x / running_speed[i] + (t - x) / biking_speed[i]);
    }
    assert(them >= 0);
    return them - me;
}

double best_running_length(int t) {
    double left = 0, right = t;
    for (int i = 0; i < 150; ++i) {
        double r1 = (2 * left + right) / 3;
        double r2 = (left + 2 * right) / 3;
        assert(r1 <= r2);
        if (margin(r1, t) < margin(r2, t)) {
            left = r1;
        } else {
            right = r2;
        }
    }
    return (left + right) / 2;
}

int main(){
    int t;
    while (cin >> t) {
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> running_speed[i] >> biking_speed[i];
            assert(running_speed[i] > eps and biking_speed[i] > eps);
        }
        
        double r = best_running_length(t);
        double m = margin(r, t);
        if (m < 0.0) {
            printf("The cheater cannot win.\n");
        } else {
            printf("The cheater can win by %.0lf seconds with r = %.2lfkm and k = %.2lfkm.\n",  m * 3600, r, t - r);
        }
    }
    return 0;
}