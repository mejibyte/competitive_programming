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

int a[MAXN], b[MAXN], c[MAXN];
long long g[MAXN];

int main(){
    int runs; scanf("%d", &runs);
    for (int run = 1; run <= runs; ++run) {
        int N, B; scanf("%d %d", &N, &B);
        long long ans = 0;
        for (int i = 1; i <= N; ++i) {
            for (int j = i; j <= N; ++j) {
                for (int k = j; k <= N; ++k) {
                    long long t = i + 1LL * j * j - 1LL * k * k * k;
                    ans += (t % B == 0);
                }
            }
        }

        printf("Case %d: %lld\n", run, ans);
    }
    return 0;
}   