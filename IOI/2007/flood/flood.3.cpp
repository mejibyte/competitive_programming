// Andrés Mejía

// Got full score on http://www.spoj.pl/OI/problems/FLOOD/

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

#define dprintf //printf

const int MAXN = 100005;

struct Point {
    int x, y;
    
    bool isLeftOf(const Point &other) const {
        if (y != other.y) return false;
        return x < other.x;
    }
    
    bool isBelow(const Point &other) const {
        if (x != other.x) return false;
        return y < other.y;
    }
} P[MAXN];

struct Wall {
    int a, b; // indeces of points
    int index;
    
    bool isVertical() const {
        return P[a].x == P[b].x;
    }
    
    bool isHorizontal() const {
        return P[a].y == P[b].y;
    }
    
    bool operator < (const Wall &other) const {
        if (isVertical()) return false;
        if (other.isVertical()) return true;
        assert(isHorizontal() and other.isHorizontal());
        return P[a].y < P[other.a].y;
    }
    
    int otherEnd(int u) const {
        assert(a == u || b == u);
        return a + b - u;
    }
    
} W[2 * MAXN];

int edge_status[2 * MAXN]; // 0 = not processed, 1 = alive, 2 = killed
int start;
int touched[2 * MAXN]; 

enum { Right, Up, Left, Down };

int g[MAXN][4];


// u = current node, dir = current direction, incoming = index of incoming edge, or -1 if root
void dfs(int u, int dir, int incoming) {
    dprintf("u = %d, dir = %d, incoming = %d\n", u + 1, dir, W[incoming].index);
    if (u == start and incoming != -1) return;
    
    for (int k = 0; k < 4; ++k) {
        int nextDir = (dir + 3 + k) % 4;
        if (g[u][nextDir] == -1) continue;
        int e = g[u][nextDir];
        if (edge_status[e] != 0) continue;
        assert( edge_status[e] == 0 );
        int v = W[e].otherEnd(u);
        
        touched[e] |= (1 << nextDir);
        dfs(v, nextDir, e);
        
        int pop = __builtin_popcount(touched[e]);
        assert(pop <= 2);
        
        if (pop == 1) {
            edge_status[e] = 2; // killed
            dprintf("On u = %d: Killing edge %d\n", u + 1, W[e].index);
        } else {
             edge_status[e] = 1; // alive
         }
        break;
    }
    
}

void walk(int start_edge, int w) {
    dprintf("walk start_edge = %d\n", W[start_edge].index);
    assert(edge_status[start_edge] == 0);
    assert(W[start_edge].isHorizontal());
    int a = W[start_edge].a, b = W[start_edge].b;
    if (P[b].isLeftOf(P[a])) swap(a, b);
    start = a;
    dfs(a, Up, -1);
}


int connect(int node, int dir, int edge) {
    assert(g[node][dir] == -1);
    g[node][dir] = edge;
}

int main(){
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &P[i].x, &P[i].y);
        for (int k = 0; k < 4; ++k) g[i][k] = -1;
    }
    int w; scanf("%d", &w);
    for (int i = 0; i < w; ++i) {
        W[i].index = i + 1;
        scanf("%d %d", &W[i].a, &W[i].b);
        W[i].a--, W[i].b--;
    }
    sort(W, W + w);
    for (int i = 0; i < w; ++i) {
        const Wall &t = W[i];
        int a = t.a, b = t.b;
        assert( a != b );
        if (t.isHorizontal()) {
            assert( P[a].isLeftOf(P[b]) || P[b].isLeftOf(P[a]) );
            if (P[b].isLeftOf(P[a])) swap(a, b);
            connect(a, Right, i);
            connect(b, Left, i);
        } else { // Vertical
            assert( P[a].isBelow(P[b]) || P[b].isBelow(P[a]) );
            if ( P[b].isBelow(P[a]) ) swap(a, b);
            connect(a, Up, i);
            connect(b, Down, i);
        }
    }
    
    
    // for (int i = 0; i < n; ++i) {
    //     for (int k = 0; k < 4; ++k) {
    //         if (g[i][k] == -1) continue;
    //         printf("From node i = %d can go to %d with direction k = %d\n", i + 1, W[g[i][k]].otherEnd(i) + 1, k);
    //     }
    // }
    
    for (int i = 0; i < w; ++i) {
        if (edge_status[i] != 0) continue;
        if (W[i].isVertical()) continue;
        walk(i, w);
    }
    
    set<int> ans;
    for (int i = 0; i < w; ++i) {
        if (edge_status[i] != 2) ans.insert(W[i].index);
    }
    printf("%d\n", (int)ans.size());
    for (set<int>::iterator i = ans.begin(); i != ans.end(); ++i) {
        printf("%d\n", *i);
    }
    
    return 0;
}