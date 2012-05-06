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

const int MAXN = 1005;

// Maximum Bipartite Matching
// Complexity: O(VE)

// Finds a maximum bipartite matching for two sets of
// size L and R.

// How to use:
// Set g[i][j] to true if element i of the Left set can
// be paired with element j of the Right set.
// Fill the table for all 0 <= i < L and 0 <= j < R.

// matchL[i] will contain i's match in the Right set
// and matchR[j] will contain j's match in the Left set.


bool g[MAXN][MAXN], seen[MAXN];
int L, R, matchL[MAXN], matchR[MAXN];

bool assign(int i) {
    for (int j = 0; j < R; ++j) if (g[i][j] and !seen[j]) {
        seen[j] = true;
        if ( matchR[j] < 0 or assign(matchR[j]) )
            return matchL[i] = j, matchR[j] = i, true;
    }
    return false;
}

int maxBipartiteMatching() {
    for (int i = 0; i < L; ++i) matchL[i] = -1;
    for (int j = 0; j < R; ++j) matchR[j] = -1;
    int ans = 0;
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < R; ++j) seen[j] = false; // or memset
        if (assign(i)) ans++;
    }
    return ans;
}

void solve() {
    int n; cin >> n;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char c; cin >> c;
            g[i][j] = (c == '1');
        }
    }
    
    L = R = n;
    int heads = n - maxBipartiteMatching();
    assert(heads <= 1);
    
    D(heads);
    
    for (int i = 0; i < n; ++i){
        printf("i = %d -> matchL[i] = %d\n", i, matchL[i]);
    }
    
    vector<int> ans;
    int cur = 0;
    for (int i = 0; i < n; ++i) {
        if (matchL[i] == -1) cur = i;
    }
    
    
    for (int k = 0; k < n; ++k) {
        ans.push_back(cur);
        if (k + 1 < n) assert(matchR[cur] != -1);
        cur = matchR[cur];
    }
    
    reverse(ans.begin(), ans.end());
    printf("Yes");
    for (int k = 0; k < n; ++k) {
        printf(" %d", ans[k]);
    }
    puts("");

}


int main(){
    int T; cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}