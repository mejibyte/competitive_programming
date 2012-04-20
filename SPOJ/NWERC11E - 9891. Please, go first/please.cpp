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

const int MAXN = 25005;
char q[MAXN];
int n;
map< char, int > last;

bool pass(char a, char b) {
    return last[a] < last[b];
}

long long score() {
    last.clear();
    for (int i = 0; i < n; ++i) last[q[i]] = i;
    long long ans = 0;
    for (int i = 0; i < n; ++i){
        ans += 1LL * i + (last[q[i]] - i);
    }
    return ans;
}

void solve() {
    long long a = score();
    sort(q, q + n, pass);
    long long b = score();
    assert(a - b >= 0);
    printf("%lld\n", 5LL * (a - b));
}

int main(){
    int T; scanf("%d", &T);
    while (T--) {
        if (scanf("%d %s", &n, q) != 2) break;
        solve();
    }
    return 0;
}