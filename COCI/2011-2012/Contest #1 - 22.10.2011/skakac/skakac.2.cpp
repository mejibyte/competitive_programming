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

map<int, set < Pair > > reach[30][30][20];

int number[30][30];

int N, T;

int di[] = { -1, -1, +1, +1, -2, -2, +2, +2 };
int dj[] = { -2, +2, -2, +2, -1, +1, -1, +1 };

inline bool inside(int r, int c) {
    return 0 <= r and r < N and 0 <= c and c < N;
}

void fill_reach(int t0) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int d = 0; t0 + (1 << d) <= T; ++d) {
                reach[i][j][0][1 << d].clear();
                for (int k = 0; k < 8; ++k) {
                    int u = i + di[k], v = j + dj[k];
                    if (!inside(u, v)) continue;
                    if ((t0 + (1 << d)) % number[u][v] == 0) {
                        printf("reach[%d][%d][%d][%d] contains (%d, %d)\n", i, j, 0, d, u, v);
                        reach[i][j][0][1 << d].insert( make_pair(u, v) );
                    }
                }
            }
        }
    }
    
    for (int k = 1; (1 << k) <= T; ++k) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int d = 0; t0 + (1 << d) <= T; ++d) {
                    reach[i][j][k][1 << d].clear();

                    foreach(p, reach[i][j][k - 1][1 << d]) {
                        int u = p->first, v = p->second;                        
                        const set<Pair> &step = reach[u][v][k-1][1 << d + 1 << (k - 1)];
                        
                        if (i == 0 and j == 0 and k == 1 and d == 0) {
                            printf("u = %d, v = %d\n", u, v);
                        }
                        
                        reach[i][j][k][d].insert( step.begin(), step.end() );
                    }
                }
            }
        }
    }
    
    printf("With t0 = %d:\n", t0);
    for (int k = 0; (1 << k) <= T; ++k) {
        printf("  In 2^k = 2^%d = %d steps:\n", k, (1 << k));
        For(i, 0, N) {
            For(j, 0, N) {
                printf("    from (%d, %d) can reach the following %d positions:\n", i, j, reach[i][j][k][0].size());
                set< Pair > s = reach[i][j][k][0];
                foreach(p, s) {
                    printf("      (%d, %d)\n", p->first, p->second);
                }
            }
        }
    }
    
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

        fill_reach(t0);
        
        foreach(p, cur) {
            int u = p->first, v = p->second;
            const set<Pair> &step = reach[u][v][k][0];
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