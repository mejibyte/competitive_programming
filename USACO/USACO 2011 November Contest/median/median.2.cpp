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

const int MAXN = 100005;
int a[MAXN];

int main(){
    #ifndef LOCAL
    freopen("median.in", "r", stdin);
    freopen("median.out", "w", stdout);
    #endif
    
    int n, x;
    scanf("%d %d", &n, &x);
    for (int i = 0; i < n; ++i){
        int cow; scanf("%d", &cow);
        a[i] = cow >= x;
    }
    
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        int zeros = 0;
        int ones = 0;
        for (int j = i; j < n; ++j) {
            zeros += a[j] == 0;
            ones += a[j] == 1;
            if (zeros <= ones) {
                ans++;
            }
        }
    }
    printf("%lld\n", ans);
    
    return 0;
}