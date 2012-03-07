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

const int MAXN = 30005;

int p[MAXN], height[MAXN], sons[MAXN], D;

int find(int u) {
    if (p[u] == u) return u;
    return p[u] = find(p[u]);
}

void hang(int a, int b) {
    if (sons[b] == D) {
        sons[b]--;
        height[b]++;
    }
    sons[b]++;
    p[a] = b;
    height[b] = max(height[b], height[a] + 1);
}

void merge(int a, int b) {
    a = find(a);
    b = find(b);
    if (sons[a] == D) {
        hang(a, b);
        return;
    }
    if (sons[b] == D) {
        hang(b, a);
        return;
    }
    if (height[a] == height[b]) {
        if (sons[a] < sons[b]) {
            hang(b, a);
        } else {
            hang(a, b);
        }
        return;
    }

    if (height[a] < height[b]) {
        hang(a, b);
    } else {
        hang(b, a);
    }
}

void solve() {
    int N; scanf("%d %d", &N, &D);
    for (int i = 0; i < N; ++i) {
        p[i] = i;
        height[i] = 1;
        sons[i] = 0;
    }

    for (int i = 1; i < N; ++i) {
        int u, v; scanf("%d %d", &u, &v);
        u--, v--;
        merge(u, v);
    }

    printf("%d\n", height[find(0)]);
}

int main(){
    int T; scanf("%d", &T);
    for (int run = 1; run <= T; ++run) {
        printf("Case #%d: ", run);
        solve();
    }
    return 0;
}