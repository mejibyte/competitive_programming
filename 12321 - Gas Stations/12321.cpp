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

pair<int, int> g[10001];

bool compare(const pair<int, int> &a, const pair<int, int> &b) {
    if (a.first != b.first) return a.first < b.first;
    return a.second > b.second;
}

int main(){
    int n;
    long long L;
    while (scanf("%lld %d", &L, &n) == 2) {
        if (L == 0 and n == 0) break;
        
        for (int i = 0; i < n; ++i) {
            long long x, r; scanf("%lld %lld", &x, &r);
            g[i].first = max(0LL, x - r);
            g[i].second = min(L, x + r);
        }
        sort(g, g + n, compare);

        if (g[0].first > 0) {
            puts("-1");
            continue;
        }
        int covered = 0;
        int ans = 0, i = 0;
        while (i < n) {
            ans++;
            int best = i;
            for (int j = i; j < n and g[j].first <= g[i].second; ++j) {
                if (g[j].second > g[best].second) {
                    best = j;
                }
            }
            covered = g[best].second;
            if (best == i) break;
            i = best;
        }
        if (covered < L) {
            puts("-1");
        } else {
            assert(ans <= n);
            printf("%d\n", n - ans);
        }
    }
    return 0;
}