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
#include <bitset>
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

int tree[MAXN];

void add(int at, int what) {
    for (at++; at < MAXN; at += at & -at) {
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

long long get(int from, int to) {
    return get(to) - get(from - 1);
}

int L[MAXN];
int T[MAXN];
int sorted_times[MAXN];

int main(){
    int n, C;
    scanf("%d %d", &n, &C);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &L[i], &T[i]);
        add(T[i], +1);
        sorted_times[i] = T[i];
    }
    sort(sorted_times, sorted_times + n);
    
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += L[i];
        ans -= 1LL * (n - i) * sorted_times[i];
    }
    printf("%lld\n", ans);
    
    // now process queries
    while (C--) {
        int who, nl, nt;
        scanf("%d %d %d", &who, &nl, &nt);
        who--;
        
        int where = lower_bound(sorted_times, sorted_times + n, T[who]) - sorted_times;
        sorted_times[where] = nt;
        T[who] = nt, L[who] = nl;
        sort(sorted_times, sorted_times + n);

        ans = 0;
        for (int i = 0; i < n; ++i) {
            ans += L[i];
            ans -= 1LL * (n - i) * sorted_times[i];
        }
        printf("%lld\n", ans);
    }
    
    return 0;
}