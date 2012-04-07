// Andrés Mejía

// Accepted

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

int tree[MAXN], N, B;

void clear() {
    for (int i = 0; i <= B + 1; ++i) {
        tree[i] = 0;
    }
}

void add(int at, int what) {
    for (at++; at <= B + 1; at += at & -at) {
        tree[at] += what;
    }
}

int get(int at) {
    int ans = 0;
    for (at++; at > 0; at -= at & -at) {
        ans += tree[at];
    }
    return ans;
}

int get(int from, int to) {
    assert(from >= 0 and to >= 0);
    return get(to) - get(from - 1);
}

inline int mod(long long x) {
    return (x % B + B) % B;
}

int main(){
    int runs; scanf("%d", &runs);
    for (int run = 1; run <= runs; ++run) {
        scanf("%d %d", &N, &B);
        clear();
        
        long long ans = 0;
        for (long long i = N; i >= 1; --i) {
            int b = mod(i * i);
            int c = mod(-i * i * i);
            assert(0 <= c and c < B);
            add(c, +1);
            ans += (i / B) * get(B - 1);
            if (i % B > 0) {
                int from = mod(-b - i);
                int to = mod(-b - 1);
                if (from <= to) {
                    ans += get(from, to);
                } else {
                    ans += get(from, B - 1) + get(0, to);
                }
            }
        }
        
        printf("Case %d: %lld\n", run, ans);
    }
    return 0;
}   