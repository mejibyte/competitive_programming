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

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

const int MAXN = 10010;
pair<int, int> g[MAXN];
int places[2 * MAXN];
int best[2 * MAXN];

bool compare(const pair<int, int> &a, const pair<int, int> &b) {
    if (a.first != b.first) return a.first < b.first;
    return a.second > b.second;
}

int main(){
    int n;
    long long L;
    while (scanf("%lld %d", &L, &n) == 2) {
        if (L == 0 and n == 0) break;
        int P = 0;
        places[P++] = 0;
        for (int i = 0; i < n; ++i) {
            long long x, r; scanf("%lld %lld", &x, &r);
            g[i].first = max(0LL, x - r);
            g[i].second = min(L, x + r);
            places[P++] = g[i].first;
            places[P++] = g[i].second;
        }
        places[P++] = L;
        sort(places, places + P);
        P = unique(places, places + P) - places;
        
        for (int i = 0; i < n; ++i) {
            g[i].first = lower_bound(places, places + P, g[i].first) - places;
            g[i].second = lower_bound(places, places + P, g[i].second) - places;
        }

        //sort(g, g + n, compare);
        // for (int i = 0; i < n; ++i) {
        //     printf("<%d, %d>\n", g[i].first, g[i].second);
        // }
        
        for (int i = 0; i < P; ++i) {
            best[i] = -1;
        }
        for (int i = 0; i < n; ++i) {
            best[g[i].first] = max(best[g[i].first], g[i].second);
        }
        for (int i = 1; i < P; ++i) {
            best[i] = max(best[i], best[i-1]);
        }
        
        // for (int i = 0; i < P; ++i) {
        //     printf("best[%d] = %d\n", i, best[i]);
        // }
        
        
        if (g[0].first < 0) {
            puts("-1");
            continue;
        }
        int ans = 0;
        int cur = 0;
        int end = lower_bound(places, places + P, L) - places;
        while (cur < end and cur < best[cur]) {
            ans++;
            cur = best[cur];
        }
        if (cur < end) {
            puts("-1");
        } else {
            assert(ans <= n);
            printf("%d\n", n - ans);
        }
    }
    return 0;
}