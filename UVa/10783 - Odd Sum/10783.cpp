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

int fast(int a, int b) {
    int p = a / 2;
    int q = (b - 1) / 2;
    return (q - p + 1) * (q + p + 1);
}

int main(){
    int runs; cin >> runs;
    for (int run = 1; run <= runs; ++run) {
        int a, b; cin >> a >> b;
        int ans = 0;
        for (int i = a; i <= b; ++i) {
            if (i & 1) ans += i;
        }
        
        // or alternatively use the closed formula
        int alternative = fast(a, b);
        assert(alternative == ans);
        
        cout << "Case " << run << ": " << ans << endl;
    }
    return 0;
}