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

const int MAXN = 2 * 50 + 5;
const int INF = INT_MAX;
vector < int > g [MAXN];
int c [MAXN][MAXN];
int f [MAXN][MAXN];
int prev [MAXN];

void refresh (int n){
    for (int i = 0; i < 2 * n; i++){
        g[i].clear();
        for (int j = 0; j < 2 * n; j++){
            f[i][j] = 0;
            c[i][j] = 0;
        }
    }
}

void join (int u, int v, int cost){
    int in_u = 2 * u;
    int out_u = 2 * u + 1;
    
    int in_v = 2 * v;
    int out_v = 2 * v + 1;
    
    g[out_u].push_back(in_v);
    g[in_v].push_back(out_u); // *** Bug
    c[out_u][in_v] += cost;
    
    g[out_v].push_back(in_u);
    g[in_u].push_back(out_v); // *** Bug
    c[out_v][in_u] += cost;
}

void join_self (int u, int cost){
    g[2 * u].push_back(2 * u + 1);
    g[2 * u + 1].push_back(2 * u); // *** Bug
    c[2 * u][2 * u + 1] += cost;
    
    //g[2 * u + 1].push_back(2 * u);
    //c[2 * u + 1][2 * u] += cost;
}

bool path(int s, int t){
    for (int i = 0; i <= t; i++)
        prev[i] = -2;
    
    queue <int> q;
    q.push(s);
    prev[s] = -1;
    while (q.size() > 0){
        int u = q.front();
        q.pop();
        if (u == t) return true;
        for (int i = 0; i < g[u].size(); i++){
            int v = g[u][i];
            if (prev[v] == -2 and c[u][v] - f[u][v] > 0){
                q.push(v);
                prev[v] = u;
            }
        }
    }
    assert(prev[t] == -2);
    return false;
}

int bottleneck(int s, int t){
    int curr = t;
    int ans = INF;
    while (curr != s){
        ans = min (ans, c[prev[curr]][curr] - f[prev[curr]][curr]);
        curr = prev[curr];
    }
    assert(prev[s] == -1);
    return ans;
}

void pump (int s, int t, int extra){
    int curr = t;
    while (curr != s){
        f[prev[curr]][curr] += extra;
        f[curr][prev[curr]] -= extra;
        curr = prev[curr];
    }
}

int max_flow(int s, int t){
    int ans = 0;
    while (true){
        // Find path
        if (!path(s, t)) break;
        // Find bottleneck
        int extra = bottleneck(s, t);
        // Pump bottleneck
        pump(s, t, extra);
        // Add flow to answer
        ans += extra;
    }
    return ans;
}

int main(){
    int nodes, edges;
    while (scanf("%d %d", &nodes, &edges) == 2){
        if (nodes == 0 and edges == 0) break;
        
        refresh(nodes);
        for (int i = 1; i < nodes - 1; i++){
            int j, cost; 
            cin >> j >> cost;
            j--;
            join_self(j, cost);
        }
        join_self(0, INF);
        join_self(nodes - 1, INF);
                
        for (int i = 0; i < edges; i++){
            int u, v, cost;
            cin >> u >> v >> cost;
            u--; v--;
            join(u, v, cost);
        }
                        
        cout << max_flow(0, 2 * nodes - 1) << endl;
        
        // for (int i = 0; i < 2 * nodes; i++){
        //             for (int j = 0; j < 2 * nodes; j++){
        //                 if (c[i][j] == INF){
        //                     cout << "oo ";
        //                 }else{
        //                     printf("%2d ", c[i][j]);
        //                 }
        //             }
        //             puts("");
        //         }
        
    }
    return 0;
}