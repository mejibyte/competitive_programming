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
#define D(x) cout << #x " is " << x << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}


const int MAXH = 1501;

/////////////// Maximum flow for sparse graphs ///////////////
///////////////    Complexity: O(V * E^2)      ///////////////

/*
Usage:
initialize_max_flow();
Create graph using add_edge(u, v, c);
max_flow(source, sink);

WARNING: The algorithm writes on the cap array. The capacity
is not the same after having run the algorithm.  If you need
to run the algorithm several times on the same graph, backup
the cap array.
*/

namespace Flow {
    const int MAXN = MAXH * 4 + 2;
    const int MAXE = (MAXH * (MAXH + 1) + 4 * MAXH); //Maximum number of edges
    const int oo = INT_MAX / 4;

    int first[MAXN];
    int next[MAXE];
    int adj[MAXE];
    unsigned short cap[MAXE];
    int current_edge;

    /*
    Builds a directed edge (u, v) with capacity c.
    Note that actually two edges are added, the edge
    and its complementary edge for the backflow.
    */
    int add_edge(int u, int v, int c){
        adj[current_edge] = v;
        cap[current_edge] = c;
        next[current_edge] = first[u];
        first[u] = current_edge++;

        adj[current_edge] = u;
        cap[current_edge] = 0;
        next[current_edge] = first[v];
        first[v] = current_edge++;
    }

    void initialize_max_flow(){
        current_edge = 0;
        memset(next, -1, sizeof next);
        memset(first, -1, sizeof first);
    }

    short q[MAXN];
    int arrived_by[MAXN];
    //arrived_by[i] = The last edge used to reach node i
    int find_augmenting_path(int src, int snk){
        /*
        Make a BFS to find an augmenting path from the source to
        the sink.  Then pump flow through this path, and return
        the amount that was pumped.
        */
        memset(arrived_by, -1, sizeof arrived_by);
        int h = 0, t = 0;
        q[t++] = src;
        arrived_by[src] = -2;
        while (h < t && arrived_by[snk] == -1){ //BFS
            int u = q[h++];
            for (int e = first[u]; e != -1; e = next[e]){
                int v = adj[e];
                if (arrived_by[v] == -1 && cap[e] > 0){
                    arrived_by[v] = e;
                    q[t++] = v;
                }
            }
        }

        if (arrived_by[snk] == -1) return 0;

        int cur = snk;
        int neck = oo;
        while (cur != src) {
            if (cap[arrived_by[cur]] < neck) neck = cap[arrived_by[cur]];
            cur = adj[arrived_by[cur] ^ 1];
        }

        cur = snk;
        while (cur != src){
            //Remove capacity from the edge used to reach node "cur"
            //Add capacity to the backedge
            cap[arrived_by[cur]] -= neck;
            cap[arrived_by[cur] ^ 1] += neck;
            //move backwards in the path
            cur = adj[arrived_by[cur] ^ 1];
        }
        return neck;
    }

    int max_flow(int src, int snk){
        int ans = 0, neck;
        while ((neck = find_augmenting_path(src, snk)) != 0){
            ans += neck;
        }
        return ans;
    }
}

const int src = MAXH * 4, sink = src + 1;

int face(int number, bool isBoy) {
    int ans = isBoy ? 0 : 2 * MAXH;
    if (number < 0) ans += -number;
    else ans += number + MAXH;
    ans -= 1500;
    //printf("number = %d, isBoy = %d, ans = %d\n", number, isBoy, ans);
    assert(ans < 4 * MAXH);
    return ans;
}

unsigned short cnt[4 * MAXH];

int main(){
    //D(Flow::maxedge);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int x; scanf("%d", &x);
        assert(1500 <= abs(x) and abs(x) <= 2500);
        int k = face(x, true);
        cnt[k]++;
        //printf("cnt[boy = %d] = %d\n", x, cnt[k]);
    }
    for (int i = 0; i < n; ++i) {
        int x; scanf("%d", &x);
        assert(1500 <= abs(x) and abs(x) <= 2500);
        int k = face(x, false);
        cnt[k]++;
        //printf("cnt[girl = %d] = %d\n", x, cnt[k]);        
    }

    //Flow::init(Flow::maxnode, src, sink);
    Flow::initialize_max_flow();

    for (int boy = -2500; boy <= -1500; ++boy) {
        if (cnt[face(boy, true)] == 0) continue;
        for (int girl = 1500; girl < -boy; ++girl) {
            if (cnt[face(girl, false)] == 0) continue;
            Flow::add_edge(face(boy, true), face(girl, false), Flow::oo);
            //printf("Added edge from boy = %d to girl = %d\n", boy, girl);
        }
    }

    for (int boy = 1500; boy <= 2500; ++boy) {
        if (cnt[face(boy, true)] == 0) continue;
        for (int girl = -boy-1; girl >= -2500; --girl) {
            if (cnt[face(girl, false)] == 0) continue;
            Flow::add_edge(face(boy, true), face(girl, false), Flow::oo);
            //printf("Added edge from boy = %d to girl = %d\n", boy, girl);
        }
    }

    for (int k = 1500; k <= 2500; ++k) {
        if (cnt[face(k, true)] > 0) {
            Flow::add_edge(src, face(k, true), cnt[face(k, true)]);
        }
        if (cnt[face(-k, true)] > 0) {
            Flow::add_edge(src, face(-k, true), cnt[face(-k, true)]);
        }

        if (cnt[face(k, false)] > 0) {
            Flow::add_edge(face(k, false), sink, cnt[face(k, false)]);
        }

        if (cnt[face(-k, false)] > 0) {
            Flow::add_edge(face(-k, false), sink, cnt[face(-k, false)]);
        }
    }

    //int ans = Flow::dinic_flow();
    int ans = Flow::max_flow(src, sink);
    cout << ans << endl;
    return 0;
}