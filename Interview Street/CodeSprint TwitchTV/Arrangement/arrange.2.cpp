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

bool g[MAXN][MAXN];
int in[MAXN], out[MAXN], n;
vector<int> path;
bool visited[MAXN];
set<int> heads, tails;

bool found;

void backtrack(int cur, int seen) {
    if (seen == n) {
        found = true;
        
        printf("Yes");
        for (int i = 0; i < n; ++i) printf(" %d", path[i]);
        puts("");
        return;
    }
    assert(visited[cur]);
    
    for (int v = 0; v < n; ++v) {
        if (g[cur][v] and !visited[v]) {
            visited[v] = true;
            path.push_back(v);
            backtrack(v, seen + 1);
            if (found) return;
            path.pop_back();
            visited[v] = false;
        }
    }

}

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        in[i] = out[i] = 0;
        visited[i] = false;
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char c; cin >> c;
            g[i][j] = (c == '1');
            if (g[i][j]) {
                out[i]++;
                in[j]++;
            }
        }
    }
    
    heads.clear();
    tails.clear();
    for (int i = 0; i < n; ++i) {
        if (in[i] == 0) heads.insert(i);
        if (out[i] == 0) tails.insert(i);
    }
    
    path.reserve(n);
    
    assert(heads.size() <= 1 and tails.size() <= 1);
    int start = 0;
    if (heads.size() > 0) {
        start = *heads.begin();
    }
    
    path.clear();
    visited[start] = true;
    path.push_back(start);

    found = false;
    backtrack(start, 1);
}


int main(){
    int T; cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}