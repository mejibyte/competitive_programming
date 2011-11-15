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

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

typedef pair<int, int> Pair;


int number[30][30];

int N, T;

int di[] = { -1, -1, +1, +1, -2, -2, +2, +2 };
int dj[] = { -2, +2, -2, +2, -1, +1, -1, +1 };

inline bool inside(int r, int c) {
    return 0 <= r and r < N and 0 <= c and c < N;
}

map<int, set< Pair > > memo[30][30][20];

set< Pair > reach(int i, int j, int k, int t) {
    if (k == 0) {
        set< Pair > ans;
        for (int p = 0; p < 8; ++p) {
            int u = i + di[p], v = j + dj[p];
            if (!inside(u, v)) continue;

            if (t % number[u][v] == 0) {
                ans.insert( make_pair(u, v) );
            }
        }
        return ans;
    }
    
    if (memo[i][j][k].count(t)) {
        return memo[i][j][k][t];
    }
    
    set< Pair > ans;
    const set< Pair > &first = reach(i, j, k - 1, t);
    foreach(p, first) {
        int u = p->first, v = p->second;
        const set< Pair > &second = reach(u, v, k - 1, t + (1 << (k - 1)));
        ans.insert(second.begin(), second.end());
    }
    return memo[i][j][k][t] = ans;
}

int main(){
    int si, sj;
    scanf("%d %d %d %d", &N, &T, &si, &sj);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            scanf("%d", &number[i][j]);
        }
    }
    
    set<Pair> cur;
    cur.insert( make_pair(si - 1, sj - 1) );
    int t0 = 0;
    
    
    while (t0 < T) {
        set<Pair> next;
        
        int k = 0;
        while (t0 + (1 << (k + 1)) <= T) k++;
        assert(t0 + (1 << k) <= T);
        assert(t0 + (1 << (k + 1)) > T);
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; (1 << k) <= T; ++k) {
                    memo[i][j][k].clear();
                }
            }
        }
        
        foreach(p, cur) {
            int u = p->first, v = p->second;
            const set<Pair> &step = reach(u, v, k, t0 + 1);
            next.insert( step.begin(), step.end() );
        }
        
        t0 += (1 << k);
        cur = next;
    }
    
    printf("%d\n", (int)cur.size());
    foreach(p, cur) {
        printf("%d %d\n", p->first + 1, p->second + 1);
    }
    return 0;
}