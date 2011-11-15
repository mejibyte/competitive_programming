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

const int MAXN = 200020;
const int SHIFT = MAXN / 2;

int a[MAXN];
long long tree[MAXN];

int add(int where, int what) {
    where += SHIFT;
    assert(where > 0);
    for (; where < MAXN; where += where & -where) {
        tree[where] += what;
    }
    return 0;
}

long long sum(int where) {
    where += SHIFT;
    assert(where > 0);
    long long ans = 0;
    for (; where > 0; where -= where & -where) {
        ans += tree[where];
    }
    return ans;
}

int main(){
    #ifndef LOCAL_ANDRES_MEJIA
    freopen("median.in", "r", stdin);
    freopen("median.out", "w", stdout);
    #endif
    
    int n, thres;
    scanf("%d %d", &n, &thres);
    
    a[0] = 0;
    for (int i = 1; i <= n; ++i){
        int cow; scanf("%d", &cow);
        a[i] = a[i-1] + (cow >= thres ? +1 : -1);
        
        add(a[i], +1);
    }
    
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        int over = a[i - 1];
        ans += sum(100001) - sum(over - 1);
        
        add(a[i], -1);
    }
    
    printf("%lld\n", ans);
    
    return 0;
}