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

const long long mod = 4207849484L;

const int MAXN = 1005;

long long ways[MAXN];

void solve() {
    int m; cin >> m;
    string s; cin >> s;
    int n = s.size();
    for (int i = 0; i <= n; ++i) ways[i] = 0;
    ways[n] = 1;
    for (int i = n - 1; i >= 0; --i) {
        if (s[i] == '0') {
            ways[i] = 0;
            continue;
        }
        
        int put = 0;
        for (int j = i; j < n; ++j) {
            put = put * 10 + s[j] - '0';
            if (put > m) break;
            ways[i] += ways[j + 1];
            ways[i] %= mod;
        }
    }
    printf("%lld\n", ways[0]);
}

int main(){
    int runs; cin >> runs;
    for (int i = 1; i <= runs; ++i){
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}