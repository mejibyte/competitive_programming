// Andrés Mejía
// Timelimit. Maybe too deep recursion?
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
const int MAXE = 2 * 100005;
const int oo = INT_MAX / 2 - 1;

int first[2][MAXN];
int next[MAXE];
int arrow[MAXE];
int weight[MAXE];
bool valid[MAXE];
int dist[2][MAXN];

int color[MAXN][2];
int memo[MAXN][2];
bool been[MAXN][2];

int nextEdge, N, S, T;

void addEdge(int g, int u, int v, int w) {
    next[nextEdge] = first[g][u];
    arrow[nextEdge] = v;
    weight[nextEdge] = w;
    first[g][u] = nextEdge;
    nextEdge++;
}

void dijkstra(int g, int start) {
    for (int i = 0; i < N; ++i) {
        dist[g][i] = oo;
    }
    dist[g][start] = 0;
    priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > q;
    q.push( make_pair(0, start) );
    while (q.size() > 0) {
        int u = q.top().second;
        int w = q.top().first;
        q.pop();
        
        if (w > dist[g][u]) continue;
        
        for (int e = first[g][u]; e > 0; e = next[e]) {
            int v = arrow[e];
            int w_extra = weight[e];
            if (w + w_extra >= dist[g][v]) continue;
            dist[g][v] = w + w_extra;
            q.push( make_pair(dist[g][v], v) );
        }
    }
}

bool cycle(int u, int day) {
    if (color[u][day] == 1) return true;
    color[u][day] = 1;
    for (int e = first[day][u]; e > 0; e = next[e]) {
        if (!valid[e]) continue;
        
        int v = arrow[e];
        if ( cycle(v, day ^ 1) ) return true;
    }
    
    color[u][day] = 2;
    return false;
}

int longest(int u, int day) {
    if (u == T) return 0;
    if (been[u][day]) return memo[u][day];
    
    int ans = -oo;
    for (int e = first[day][u]; e > 0; e = next[e]) {
        if (!valid[e]) continue;
        
        int v = arrow[e];
        int w = weight[e];
        
        int option = w + longest(v, day ^ 1);
        if (option > ans) ans = option;
        
    }
    been[u][day] = true;
    memo[u][day] = ans;
    return ans;
}

int main(){
    nextEdge = 1;
    scanf("%d %d %d", &N, &S, &T);
    S--, T--;

    for (int g = 0; g < 2; ++g) {
        int m; scanf("%d", &m);
        for (int k = 0; k < m; ++k) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            u--, v--;
            
            addEdge(g, u, v, w);
            addEdge(g, v, u, w);
        }
    }
    
    dijkstra(0, T);
    dijkstra(1, T);
    
    // for (int g = 0; g < 2; ++g) {
    //     for (int i = 0; i < N; ++i) {
    //         printf("dist[%d][%d] = %d\n", g, i + 1, dist[g][i]);
    //     }
    // }
    
    for (int g = 0; g < 2; ++g) {
        for (int i = 0; i < N; ++i) {
            for (int e = first[g][i]; e > 0; e = next[e]) {
                valid[e] = (dist[g][i] > dist[g][arrow[e]] );
                // printf("Graph %d: Edge %d, from %d to %d with weight %d is %d-valid\n", g, e, i + 1, arrow[e] + 1, weight[e], valid[e] );
            }
        }
    }
    
    bool c = cycle(S, 0);
    if (c) {
        puts("-1");
    } else {
        int ans = longest(S, 0);
        assert(ans > 0);
        printf("%d\n", ans);
    }
    
    return 0;
}