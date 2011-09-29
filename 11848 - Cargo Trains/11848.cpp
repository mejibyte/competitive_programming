// Accepted
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

typedef pair<int, long long> edge; // first = weight, second = node

const int MAXN = 105;

vector< edge > ga[MAXN], gb[MAXN];

long long g[MAXN][MAXN][2];

double d[MAXN];

int shortestPath(int start, int end, double percentage, int N) {
    for (int i = 0; i < N; ++i) {
        d[i] = 1e200;
    }
    
    d[start] = 0.0;
    priority_queue < pair< double, int >, vector< pair<double, int> >, greater< pair<double, int> > > q;
    q.push(  make_pair(0.0, start) );

    while (q.size() > 0) {
        int u = q.top().second;
        double w = q.top().first;
        q.pop();
        
        if (w > d[u]) continue;
        if (u == end) return floor(w);
        
        for (int v = 0; v < N; ++v) {
            if (g[u][v][0] == -1 and g[u][v][1] == -1) continue;

            double extra;
            if (g[u][v][0] != -1 and g[v][u][1] != -1) {
                extra = percentage * g[u][v][0] + (1.0 - percentage) * g[u][v][1];
            } else {
                extra = max(g[u][v][0], g[u][v][1]);   
            }
            if (w + extra < d[v]) {
                d[v] = w + extra;
                q.push( make_pair(w + extra, v) );
            }            
        }
    }
    assert(false);
}


int main(){
    
    //printf("2.9 = %d 2.1 = %d, 2.999999999999999999999 = %d, 2.5 = %d, 2.0 = %d\n", (int)2.9, (int)2.1, (int)2.999999999999999999999, (int)2.5, (int)2.0);
    
    int numCities, numEdgesA, numEdgesB, combinations;
    while (cin >> numCities >> numEdgesA >> numEdgesB >> combinations) {     
        if (numCities == -1 and numEdgesA == -1 and numEdgesB == -1 and combinations == -1) break;
        /*the number of cities, the number of edges in the network of company A, 
        the number of edges in the network of company B, 
        and the number of combination alternatives respectively.
        */
        for (int i = 0; i < numCities; ++i) {
            for (int j = 0; j < numCities; ++j) {
                g[i][j][0] = g[i][j][1] = -1;
            }
        }
        for (int k = 0; k < numEdgesA; ++k) {
            int u, v; long long w;
            cin >> u >> v >> w;
            assert(g[u][v][0] == -1 and g[v][u][0] == -1);            
            g[u][v][0] = w;
            g[v][u][0] = w;
        }
        for (int k = 0; k < numEdgesB; ++k) {
            int u, v; long long w;
            cin >> u >> v >> w;
            assert(g[u][v][1] == -1 and g[v][u][1] == -1);            
            g[u][v][1] = w;
            g[v][u][1] = w;
        }
        
        for (int k = 0; k < combinations; ++k) {
            double c;
            cin >> c;
            cout << shortestPath(0, numCities - 1, c, numCities) << endl;
        }
    }
    
    
    return 0;
}