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

const int MAXN = 2005;

int see[MAXN];
int height[MAXN];

long double angle(int from, int to) {
    //printf("Angle from %d to %d\n", from, to);
    int d = to - from;
    int h = height[to] - height[from];
    //printf("  d = %d, h = %d\n", d, h);
    return atan2(h, d);
}

void solve() {
    int n; cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        cin >> see[i];
        see[i]--;
    }
    height[n - 1] = 1;
    for (int i = n - 2; i >= 0; --i) {
        height[i] = 1;
        for (int k = see[i]; k < n; ++k) height[k]++;
    }
    
    bool valid = true;
    for (int i = 0; i < n - 1; ++i) {
        for (int k = i + 1; k < n; ++k) {
            if (cmp(angle(i, k), angle(i, see[i])) > 0 ) {
                printf("Angle from i=%d to k=%d is greater than angle from i=%d to see[i]=%d\n", i, k, i, see[i]);
                valid = false;
            }
        }
    }
  
    if (!valid) {
        puts("Impossible");
//        return;
    }
    
    for (int i = 0; i < n; ++i) {
        if (i > 0) printf(" ");
        printf("%d", height[i]);
    }
    puts("");
}

int main(){
    int T; cin >> T;
    for (int i = 1; i <= T; ++i) {
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}