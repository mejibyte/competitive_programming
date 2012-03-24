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

namespace IO {
   #define MAXBUFF (1<<18)
    char buffer[MAXBUFF], *p = buffer+MAXBUFF;

    inline char read_char() {
        if( p == buffer+MAXBUFF ) {
            fread( buffer, 1, MAXBUFF, stdin );
            p = buffer;
        }
        return *p++;
    }

    inline int read_unsigned_int() {
        char c;
        while( !isdigit(c = read_char()) );
        int ret = c-'0';
        while( isdigit(c = read_char()) ) ret = ret * 10 + c-'0';
        return ret;
    }
}



const int MAXN = 10005;

vector<int> g[MAXN];
int p[MAXN], d[MAXN], low[MAXN], tick;

int find(int x) {
    return p[x] == x ? x : p[x] = find(p[x]);
}

int link(int x, int y) {
    int a = find(x), b = find(y);
    if (a != b) {
        p[a] = b;
    }
}

void dfs(int u, int parent = -1) {
    d[u] = low[u] = tick++;
    foreach(out, g[u]) {
        int v = *out;
        if (v == parent) continue;
        if (d[v] == -1) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
        } else {
            low[u] = min(low[u], d[v]);
        }
        
        if (low[v] > d[u]) {
            //printf("edge from %d to %d is a bridge\n", u + 1, v + 1);
            link(u, v);
        }
    }
}

int main(){
    int n, e, q;
    while (true) {
        n = IO::read_unsigned_int(), e = IO::read_unsigned_int(), q = IO::read_unsigned_int();
        if (n == 0 and e == 0 and q == 0) break;
        
        for (int i = 0; i < n; ++i) {
            g[i].clear();
            p[i] = i;
            d[i] = -1;
        }
        // read edges
        for (int i = 0; i < e; ++i) {
            int u = IO::read_unsigned_int(), v = IO::read_unsigned_int();
            u--, v--;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        
        tick = 0;
        for (int i = 0; i < n; ++i) {
            if (d[i] == -1) dfs(i);
        }
        
        // read queries
        for (int i = 0; i < q; ++i) {
            int u = IO::read_unsigned_int(), v = IO::read_unsigned_int();
            u--, v--;
            
            if (find(u) == find(v)) {
                puts("Y");
            } else {
                puts("N");
            }
        }
        puts("-");
    }
    return 0;
}