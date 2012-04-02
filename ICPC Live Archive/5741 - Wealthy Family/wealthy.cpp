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

const int MAXN = 150005;

vector<int> g[MAXN];
int stamp;
vector<int> jump, nodes, wealth;

int dfs(int u) {
    int ans = INT_MAX;
    for (int i = 0; i < g[u].size(); ++i) {
        ans = min(ans, dfs(g[u][i]));
    }
    ans = min(ans, stamp);
    stamp++;
    jump.push_back(ans);
    nodes.push_back(u);
    return ans;
}

int main(){
    int N, K;
    while (scanf("%d %d", &N, &K) == 2) {
        for (int i = 0; i <= N; ++i) {
            g[i].clear();
        }
        jump.assign(1, -1);
        nodes.assign(1, -1);
        wealth.resize(N + 1);
        
        int root = -1;
        for (int i = 1; i <= N; ++i) {
            int p;
            scanf("%d %d", &p, &wealth[i]);
            if (p == 0) root = i;
            else g[p].push_back(i);
        }
        stamp = 0;
        dfs(root);
        
        // puts("wealth:");
        // for (int i = 0; i <= N; ++i) printf("%d ", wealth[i]); puts("");
        // puts("Nodes:");
        // for (int i = 0; i <= N; ++i) printf("%d ", nodes[i]); puts("");
        // for (int i = 0; i <= N; ++i) printf("%d ", jump[i]); puts("");
        
        vector<int> dp(N + 1, 0); // Using 0 nodes
        for (int k = 1; k <= K; ++k) {
            vector<int> next(N + 1);
            next[0] = INT_MIN;
            for (int i = 1; i <= N; ++i) {
                assert(jump[i] >= 0);
                next[i] = max(next[i - 1], dp.at(jump[i]) + wealth.at(nodes[i]) );
            }
            dp = next;
        }
        if (dp[N] < 0) {
            printf("impossible\n");
        } else {
            printf("%d\n", dp[N]);
        }
    }
    return 0;
}