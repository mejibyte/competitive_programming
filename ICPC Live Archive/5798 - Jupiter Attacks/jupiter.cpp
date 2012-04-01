// Andrés Mejía

// Accepted (0.892s).

// This solution uses a Fenwick tree to keep the sum
// a[1] * B^(n - 1) + a[2] * B^(n - 2) + ... + a[n - 1] * B^1 + a[n] * B^0.

// - Updating the value at position i is just changing what's currently there for new_value * B^(n - i).
// - Finding the hash from i to j (inclusive) is the same as finding (a[i] * B^(n - i) + ... + a[j] * B^(n - j)) / B^(n - j).
//   Thus we need to find the value of S / T (mod p) (where S is the sum above --found using the Fenwick tree-- and
//   T is just B^(n - j)).
//   We can't use division because this number is huge, but since we only care about the value of this number mod P
//   we can use Fermat's Little Theorem to quickly find the multiplicative inverse of T and find the solution:
//   We want to find x in S / T === x (mod P).
//   Multiplying both sides by T, we get: S === T * x (mod p).  Multiplying both sides by the multiplicative inverse of T, we
//   get: S * Inverse(T) ===  T * Inverse(T) * x === x (mod p). In other words, x is just s * inverse(T) (mod P).
//   And since P is prime, Inverse(T) is just T^(P - 2) (this is Fermat's Little Theorem).


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
    for (at++; at < MAXN; at += at & -at) {
        tree[at] = mod(tree[at] + what);
    }
}

int query(int at) {
    int ans = 0;
    for (at++; at > 0; at -= at & -at) {
        ans = mod(ans + tree[at]);
    }
    return ans;
}

int at(int u) {
    return mod(query(u) - query(u - 1));
}

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
        memset(tree, 0, sizeof tree);
        while (queries--) {
            char type;
            int u, v;
            scanf(" %c %d %d ", &type, &u, &v);
            if (type == 'E') {
                add(u, -at(u));
                assert(at(u) == 0);
                add(u, (1LL * v * power(B, N - u)) % P);
            } else {
                int s = mod(query(v) - query(u - 1));
                int t = power(B, N - v);
                int ans = (1LL * s * power(t, P - 2)) % P;
                printf("%d\n", ans);
            }
        }
        puts("-");
    }
    return 0;
}