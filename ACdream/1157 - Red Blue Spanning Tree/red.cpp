// Andrés Mejía

// Accepted.

// Problem statement: http://www.acdream.net/problem.php?id=1157

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
    int u, v;
    char color;
};

bool red_first(const Edge &a, const Edge &b) {
    return a.color > b.color;
}

bool blue_first(const Edge &a, const Edge &b) {
    return a.color < b.color;
}


void solve(int n, int m, int k) {
    assert(n < MAXN);
    
    vector<Edge> e(m);
    for (int i = 0; i < m; ++i) {
        cin >> e[i].color >> e[i].u >> e[i].v;
        e[i].u--, e[i].v--;
    }
    
    int low = 0, high = 0;
    
    sort(e.begin(), e.end(), red_first);

    reset(n);
    
    for (int i = 0; i < m; ++i) {
        const Edge &edge = e.at(i);
        char color = edge.color;
        int u = edge.u, v = edge.v;
        
        if (find(u) == find(v)) continue;
        link(u, v);
        low += (color == 'B');
    }

    sort(e.begin(), e.end(), blue_first);

    reset(n);
    
    for (int i = 0; i < m; ++i) {
        const Edge &edge = e.at(i);
        char color = edge.color;
        int u = edge.u, v = edge.v;

        if (find(u) == find(v)) continue;
        link(u, v);
        high += (color == 'B');
    }
    
    cout << (low <= k and k <= high) << endl;
    
}


int main(){
    int n, m, k;
    while (cin >> n >> m >> k) {
        if (n == 0 and m == 0 and k == 0) break;
        solve(n, m, k);
    }
    return 0;
}