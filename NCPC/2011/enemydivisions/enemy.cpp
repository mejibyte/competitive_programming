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

vector<int> g[MAXN];

int color[MAXN];
set<int> with_enemies[4];

int enemies(int u) {
    int ans = 0;
    assert(g[u].size() <= 3);
    for (int i = 0; i < g[u].size(); ++i) {
        int v = g[u][i];
        ans += (color[u] == color[v]);
    }
    assert(0 <= ans and ans <= 3);
    return ans;
}

int main(){
    int n, e;
    cin >> n >> e;
    while (e--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 0; i < n; ++i) {
        assert(g[i].size() <= 3);
        with_enemies[enemies(i)].insert(i);
    }
    
    while (with_enemies[3].size() > 0 or with_enemies[2].size() > 0) {
        for (int k = 3; k >= 2; --k) {
            while (with_enemies[k].size() > 0) {
                int u = *with_enemies[k].begin();
                with_enemies[k].erase(u);
                color[u] ^= 1;
                with_enemies[enemies(u)].insert(u);
                for (int i = 0; i < g[u].size(); ++i) {
                    int v = g[u][i];
                    for (int j = 0; j <= 3; ++j) with_enemies[j].erase(v);
                    with_enemies[enemies(v)].insert(v);
                }
            }
        }
    }
    
    vector< vector<int> > ans(2);
    for (int i = 0; i < n; ++i) ans[color[i]].push_back(i);
    if (ans.back().empty()) ans.pop_back();
    printf("%d\n", ans.size());
    for (int i = 0; i < ans.size(); ++i) {
        for (int j = 0; j < ans[i].size(); ++j) {
            if (j > 0) printf(" ");
            printf("%d", ans[i][j] + 1);
        }
        printf("\n");
    }
    
    return 0;
}