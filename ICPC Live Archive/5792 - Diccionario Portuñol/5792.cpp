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

const int MAXN = 1005;
const int MAXS = 100005;
int P, S;

int next[MAXS][26];
bool end[MAXS];

string portuguese[MAXN], spanish[MAXN];

int under[MAXS];

void dfs(int u) {
    under[u] = 0;
    for (int c = 0; c < 26; ++c) {
        if (next[u][c] != -1) {
            dfs(next[u][c]);
            under[u] += under[ next[u][c] ];
            under[u] += end[ next[u][c] ];
        }
    }
}

int lcp(const string &s, const string &p) {
    int ans = 0;
    for (; ans < s.size() and ans < p.size() and s[ans] == p[ans]; ans++);
    return ans;
}

void solve() {
    memset(next, -1, sizeof next);
    memset(end, false, sizeof end);
    
    sort(portuguese, portuguese + P);
    
    int nextState = 1;
    for (int k = 0; k < S; ++k) {
        const string &s = spanish[k];
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            int state = 0;
            for (int j = i; j < n; ++j) {
                int c = s[j] - 'a';
                if (next[state][c] == -1) {
                    next[state][c] = nextState++;
                    if (nextState >= MAXS) {
                        puts("Too big for me.");
                        return;
                    }
                }
                state = next[state][c];
            }
            end[state] = true;
        }
    }
    dfs(0);
    
    long long ans = 0;
    for (int i = 0; i < P; ++i) {
        int l = i > 0 ? lcp(portuguese[i], portuguese[i - 1]) ? 0;
        int s = 0;
        ans += under[0];
        
    }
}

int main(){
    while (scanf("%d %d ", &P, &S) == 2){
        if (P == 0 and S == 0) break;
        
        static char buf[MAXN];
        for (int i = 0; i < P; ++i) {
            gets(buf);
            portuguese[i] = string(buf);
        }
        for (int i = 0; i < S; ++i) {
            gets(buf);
            spanish[i] = string(buf);
        }
        solve();
    }
    return 0;
}