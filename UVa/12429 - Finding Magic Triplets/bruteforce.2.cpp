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
        
        for (int i = 0; i < B; ++i) g[i] = 0;
        for (int i = 1; i <= N; ++i) {
            a[i] = i % B;
            b[i] = (1LL * i * i) % B;
            c[i] = B - (1LL * i * i * i) % B;
            if (c[i] == B) c[i] = 0;
        }
        
        // for (int i = 1; i <= N; ++i) {
        //     printf("i = %d:\n", i);
        //     printf("  i^2 = %lld, i^2 mod B = %d, b[i] = %d\n", 1LL * i * i, (1LL * i * i) % B, b[i]);
        //     printf("  i^3 = %lld, i^3 mod B = %d, -i^3 mod B = %d, c[i] = %d\n", 1LL * i * i * i, (1LL * i * i * i) % B, ((-1LL * i * i * i) % B + B) % B, c[i]);
        // }
        
        long long ans = 0;
        
        for (int i = 1; i <= N; ++i) {
            for (int j = i; j <= N; ++j) {
                for (int k = j; k <= N; ++k) {
                    int t = (a[i] + b[j]) % B + c[k];
                    ans += (t % B == 0);
                }
            }
        }
        
        printf("Case %d: %lld\n", run, ans);
    }
    return 0;
}   