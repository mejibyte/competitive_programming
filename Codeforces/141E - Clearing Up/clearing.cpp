// Andrés Mejía

// Accepted

// See also http://apps.topcoder.com/forums/?module=Thread&threadID=745792&start=0&mc=3#1534322

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

const int MAXN = 10005;

// Union find
int p[MAXN];

int find(int x) {
    return p[x] == x ? x : p[x] = find(p[x]);
}

void link(int u, int v) {
    int a = find(u), b = find(v);
    p[a] = b;
}

void reset(int n) {
    for (int i = 0; i < n; ++i) {
        p[i] = i;
    }
}

struct Edge {
    int u, v, index;
    char color;
};

bool santa_first(const Edge &a, const Edge &b) {
    return a.color < b.color;
}

bool elf_first(const Edge &a, const Edge &b) {
    return a.color > b.color;
}


void solve(int n, int m) {
    
    if (n % 2 == 0) {
        puts("-1");
        return;
    }
    
    assert(n < MAXN);
    
    vector<Edge> santa, elf;
    for (int i = 0; i < m; ++i) {
        Edge e;
        cin >> e.u >> e.v >> e.color;
        e.u--, e.v--;
        e.index = i + 1;
        
        if (e.color == 'M') santa.push_back(e);
        else elf.push_back(e);
    }


    int need = (n - 1) / 2;
    int santa_has = 0, elf_has = 0;

    // first, find Santa's edges that are necessary, by choosing first all Elf's edges.
    reset(n);
    for (int i = 0; i < elf.size(); ++i) {
        const Edge &edge = elf.at(i);
        int u = edge.u, v = edge.v;
        if (find(u) != find(v)) {
            link(u, v);
        }
    }
    
    vector<int> necessary;
    
    for (int i = 0; i < santa.size(); ++i) {
        const Edge &edge = santa.at(i);
        int u = edge.u, v = edge.v;
        if (find(u) != find(v)) {
            link(u, v);
            necessary.push_back(i);
        }
    }

    vector<int> ans;
    reset(n);
    // now rebuild the answer. Pick first the edges that are necessary
    for (int k = 0; k < necessary.size(); ++k) {
        const Edge &edge = santa[necessary[k]];
        int u = edge.u, v = edge.v;
        assert(find(u) != find(v));
        link(u, v);
        santa_has++;
        ans.push_back(edge.index);
    }
    
    // now take missing Santa edges
    for (int i = 0; i < santa.size() and santa_has < need; ++i) {
        const Edge &edge = santa.at(i);
        int u = edge.u, v = edge.v;
        if (find(u) == find(v)) continue;
        link(u, v);
        ans.push_back(edge.index);
        santa_has++;
        if (santa_has == need) break;
    }

    // now finish the spanning tree with Elf's edges
    for (int i = 0; i < elf.size(); ++i) {
        const Edge &edge = elf.at(i);
        int u = edge.u, v = edge.v;
        if (find(u) == find(v)) continue;
        link(u, v);
        ans.push_back(edge.index);
        elf_has++;
    }

    if (santa_has != need or elf_has != need) {
        puts("-1");
    } else {
        assert(ans.size() == n - 1);
        printf("%d\n", n - 1);
        for (int i = 0; i < ans.size(); ++i) printf("%d ", ans[i]);
        puts("");
    }
}


int main(){
    int n, m;
    cin >> n >> m;
    solve(n, m);
    return 0;
}