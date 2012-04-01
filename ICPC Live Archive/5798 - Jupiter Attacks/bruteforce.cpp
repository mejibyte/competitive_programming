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

int N, B, P;

int a[MAXN];

int power(int a, int b) {
    assert(b >= 0);
    if (b == 0) return 1;
    if (b & 1) { // odd
        return (1LL * a * power(a, b - 1)) % P;
    } else {
        int half = power(a, b / 2);
        return (1LL * half * half) % P;
    }
}


int main(){
    int queries;
    while (scanf(" %d %d %d %d ", &B, &P, &N, &queries) == 4) {
        if (B == 0 and P == 0 and N == 0 and queries == 0) break;
        memset(a, 0, sizeof a);
        while (queries--) {
            char type;
            int u, v;
            scanf(" %c %d %d ", &type, &u, &v);
            if (type == 'E') {
                a[u] = v % P;
            } else {
                int ans = 0;
                for (int i = u; i <= v; ++i) {
                    ans += (1LL * a[i] * power(B, v - i)) % P;
                    ans %= P;
                }
                printf("%d\n", ans);
            }
        }
        puts("-");
    }
    return 0;
}