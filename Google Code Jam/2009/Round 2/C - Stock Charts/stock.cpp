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

const int MAXN = 105;

bool below(const vector<int> &a, const vector<int> &b) {
    for (int i = 0; i < a.size(); ++i) 
        if (a[i] >= b[i]) return false;
    return true;
}

bool g[MAXN][MAXN];
int matchR[MAXN], n;
bitset<MAXN> seen;

bool assign(int u) {
    for (int v = 0; v < n; ++v) {
        if (!g[u][v] or seen[v]) continue;
        seen[v] = true;
        if (matchR[v] == -1 or assign(matchR[v])) {
            matchR[v] = u;
            return true;
        }
    }
    return false;
}

void solve() {
    int k;
    cin >> n >> k;
    vector< vector<int> > stock;
    for (int i = 0; i < n; ++i) {
        vector<int> prices;
        for (int j = 0; j < k; ++j) {
            int x; cin >> x;
            prices.push_back(x);
        }
        stock.push_back( prices );
    }
    memset(g, 0, sizeof g);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            g[i][j] = below(stock[i], stock[j]);
        }
    }
    
    int ans = 0;
    memset(matchR, -1, sizeof matchR);
    seen.reset();
    for (int i = 0; i < n; ++i) {
        seen.reset();
        bool increase = assign(i);
        if (increase) ans++;
    }
    cout << n - ans << endl;
}

int main(){
    int runs;
    cin >> runs;
    for (int i = 1; i <= runs; ++i) {
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}