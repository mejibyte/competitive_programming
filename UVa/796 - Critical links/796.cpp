#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <bitset>
using namespace std;

vector<bool> visited;
vector<int> prev, low, d;
vector< vector<int> > g;
vector< vector<bool> > is_bridge;
int n, ticks;

void dfs(int u){
    visited[u] = true;
    d[u] = low[u] = ticks++;
    for (int i=0; i<g[u].size(); ++i){
        int v = g[u][i];
        if (prev[u] != v){
            if(!visited[v]){
               prev[v] = u;
               dfs(v);
               if (d[u] < low[v]){
                   is_bridge[u][v] = is_bridge[v][u] = true;
               }
               low[u] = min(low[u], low[v]);
            }else{
               low[u] = min(low[u], d[v]);
            }
        }
    }
}

int main(){
    while (scanf("%d", &n)==1){
        visited.assign(n, false);
        prev.assign(n, -1);
        low.resize(n);
        d.resize(n);
        g.assign(n, vector<int>());
        is_bridge.assign(n, vector<bool>(n, false)); //is_bridge[i][j]
        if (n == 0){ printf("0 critical links\n\n"); continue; }
        
        for (int i=0; i<n; ++i){
            int node, deg;
            scanf("%d (%d)", &node, &deg);
            g[node].resize(deg);
            for (int k=0, x; k<deg; ++k){
                scanf("%d", &x);
                g[node][k] = x;
            }
        }
        
        ticks = 0;
        for (int i=0; i<n; ++i){
            if (!visited[i]){
                dfs(i);
            }
        }
        
        int cnt = 0;
        for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) cnt += is_bridge[i][j];
        cnt /= 2;
        printf("%d critical links\n", cnt);
        for (int i=0; i<n; ++i){
            for (int j=i+1; j<n; ++j){
                if (is_bridge[i][j]){
                    printf("%d - %d\n", i, j);
                }
            }
        }
        printf("\n");
        
    }
    return 0;
}
