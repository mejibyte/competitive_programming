// Andrés Mejía

// Passes all test cases with 0.95s and 22600 kB in the worst case.

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

#define SIZE(t) ((int)((t).size()))

struct FenwickTree {
    int N;
    vector<int> d;
    FenwickTree(int length) : N(length + 1), d(N) { }

    void update(int at, int by) {
        assert(at >= 0);
        assert(at + 1 < N);
        for (at++; at < N; at += at & -at) {
            d[at] += by;
        }
    }

    long long query(int at) {
        assert(at >= 0);
        assert(at + 1 < N);
        int ans = 0;
        for (at++; at > 0; at -= at & -at) {
            ans += d[at];
        }
        return ans;
    }

    // returns sum[from, to]
    long long query(int from, int to) {
        int ans = query(to);
        if (from - 1 >= 0) ans -= query(from - 1);
        return ans;
    }
};

// the original tree
int N;

// rooted tree as parent/child edges
vector<vector<int> > children;
vector<int> parent;

vector<int> subtree_size;

// heavy-light decomposition of the tree into paths
vector<int> path_id, path_offset, path_head, path_length;

// sum for each path
vector< FenwickTree > trees;

void dfs() {
    subtree_size.clear(); subtree_size.resize(N);
    vector<bool> visited(N,false);
    vector<int> walk;
    
  // run the DFS to compute lots of information
    stack<int> vertex, edge;
    visited[0]=true; parent[0]=0;
    vertex.push(0); edge.push(0);
    while (!vertex.empty()) {
        int kde = vertex.top(); vertex.pop();
        int e = edge.top(); edge.pop();
        if (e == SIZE(children[kde])) {
            walk.push_back(kde);
            subtree_size[kde] = 1;
            for (int i=0; i<SIZE(children[kde]); ++i) subtree_size[kde] += subtree_size[children[kde][i]];
        } else {
            vertex.push(kde); edge.push(e+1);
            int kam = children[kde][e];
            if (!visited[kam]) { 
                visited[kam]=true;
                vertex.push(kam); edge.push(0);
            }
        }
    }

    path_id.clear(); path_id.resize(N);
    path_offset.clear(); path_offset.resize(N);
    path_head.clear();
    path_length.clear();
    trees.clear();

    int pathCount = 0;
  // compute the heavy-light decomposition
    vector<bool> parent_edge_processed(N,false);
    parent_edge_processed[0] = true;
    for (int i=0; i<SIZE(walk); ++i) {
        int w = walk[i];
        if (parent_edge_processed[w]) continue;
        vector<int> this_path;
        this_path.push_back(w); 
        while (1) {
            bool is_parent_edge_heavy = (2*subtree_size[w] >= subtree_size[parent[w]]);
            parent_edge_processed[w] = true;
            w = parent[w];
            this_path.push_back(w);
            if (!is_parent_edge_heavy) break;
            if (parent_edge_processed[w]) break;
        }

        for (int j = 0; j < SIZE(this_path)-1; ++j) {
            path_id[ this_path[j] ] = pathCount;
            path_offset[ this_path[j] ] = j;
        }
        path_head.push_back(this_path.back());
        path_length.push_back( SIZE(this_path) );
        trees.push_back( FenwickTree( SIZE(this_path)) );
        pathCount++;
    }

    path_head.push_back(-1);
    path_length.push_back(2);
    trees.push_back( FenwickTree(2) );
    path_id[0] = pathCount++;
    path_offset[0] = 0;
}

vector< int > initial_salary;

void update(int node, int by) {
    int p = path_id[node];
    int at = path_offset[node];
    trees[p].update(at, by);
}


int get(int node) {
    int ans = initial_salary[node];
    int p = path_id[node];
    int at = path_offset[node];
    ans -= trees[p].query(at, at); // an employee doesn't affect himself

    while (node >= 0) {
        p = path_id[node];
        at = path_offset[node];
        int len = path_length[p] - 1;
        ans += trees[p].query(at, len);
        node = path_head[p];
    }
    return ans;
}

int main(){
    int Q;
    cin >> N >> Q;

    parent.clear(); parent.resize(N);
    children.clear(); children.resize(N);

    initial_salary.resize(N);
    cin >> initial_salary[0];

    for (int i=1; i<N; ++i) {
        int p;
        cin >> initial_salary[i] >> p;
        p--;
        children[p].push_back(i);
        parent[i] = p;
    }
    dfs();

    for (int q = 0; q < Q; ++q) {
        char type; scanf(" %c ", &type);
        if (type == 'p') { // increase
            int u, delta;
            scanf("%d %d", &u, &delta);
            u--;
            update(u, delta);
        } else { // how much?
            int u; scanf("%d", &u);
            u--;
            printf("%d\n", get(u));
        }
    }
    return 0;
}