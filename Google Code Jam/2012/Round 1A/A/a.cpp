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

const int MAXN = 100005;

double p[MAXN];

void solve() {
    int a, b; cin >> a >> b;
    for (int i = 0; i < a; ++i) cin >> p[i];
    
    long double all_good = 1.0;
    for (int i = 0; i < a; ++i) all_good *= p[i];
    
    long double option1 = (b - a + 1) * all_good + (2*b - a + 2) * (1.0 - all_good);
    long double option3 = b + 2;
    
    long double option2 = 1e100;
    
    all_good = 1.0;
    for (int k = 0; k < a; ++k) {
        long double score = a - k + all_good * (b - k + 1) + (1.0 - all_good) * (2*b - k + 2);
        option2 = min(option2, score);
        all_good *= p[k];
    }

    double ans = min(option1, min(option2, option3));
    printf("%.8lf\n", ans);
    
}

int main(){
    int T; cin >> T;
    for (int run = 1; run <= T; ++run) {
        printf("Case #%d: ", run);
        solve();
    }
    return 0;
}
