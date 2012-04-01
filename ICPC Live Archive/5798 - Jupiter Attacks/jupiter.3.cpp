// Andrés Mejía

// Accepted.

// Like jupiter.2.cpp, but uses the Extended Euclidean Algorithm to find the modular inverse instead of Fermat's Little Theorem.

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

int tree[MAXN];

inline int mod(int a) {
    return ((a % P) + P) % P;
}

void add(int at, int what) {
    what %= P;
    for (at++; at <= N + 1; at += at & -at) {
        tree[at] = mod(tree[at] + what);
    }
}

int query(int at) {
    int ans = 0;
    for (at++; at > 0; at -= at & -at) {
        ans += tree[at];
        if (ans >= P) ans -= P;
    }
    return ans;
}

int at(int u) {
    return mod(query(u) - query(u - 1));
}

// Assumes gcd(a, n) == 1 and a > 0.
long long modInverse(long long a, long long n) {
    long long i = n, v = 0, d = 1;
    while (a > 0) {
        long long t = i / a, x = a;
        a = i % x;
        i = x;
        x = d;
        d = v - t * x;
        v = x;
    }
    v %= n;
    if (v < 0) v += n;
    return v;
}

int main(){
    int queries;
    while (scanf(" %d %d %d %d ", &B, &P, &N, &queries) == 4) {
        if (B == 0 and P == 0 and N == 0 and queries == 0) break;
        static int base[MAXN];
        base[0] = 1;
        for (int i = 0; i <= N + 1; ++i) {
            tree[i] = 0;
            if (i > 0) base[i] = (1LL * base[i - 1] * B) % P;
        }
        
        while (queries--) {
            char type;
            int u, v;
            scanf(" %c %d %d ", &type, &u, &v);
            if (type == 'E') {
                add(u, -at(u));
                add(u, (1LL * v * base[N - u]) % P);
            } else {
                int s = mod(query(v) - query(u - 1));
                int t = base[N - v];
                int ans = (1LL * s * modInverse(t, P)) % P;
                printf("%d\n", ans);
            }
        }
        puts("-");
    }
    return 0;
}