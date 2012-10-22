using namespace std;
#include <iostream>
#include <algorithm>
#include <iterator>
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
#include <map>
#include <set>
#include <stack>

#define D(x) cout << #x " = " << (x) << endl
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); x++)
#define For (i, a, b) for (int i = (a); i < (b); i++)

const int INF = 1 << 29;
int d[105][105];
int shortest[105][105];

vector<int> path;

bool is_shortest(int i, int j) {
    int total = 0;
    for (int k = i; k + 1 <= j; ++j) {
        total += d[path[k]][path[k+1]];
    }
    return total == shortest[i][j];
}


int main (){
    int n, run = 1;
    while (cin >> n){
        if (n == 0) break;
        printf("Case %d: ", run++);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                cin >> d[i][j];
                if (d[i][j] == 0) d[i][j] = INF;
            }    
            d[i][i] = 0;
        }
        
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                shortest[i][j] = d[i][j];
            }
        }
        
        
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    shortest[i][j] = min(shortest[i][j], shortest[i][k] + shortest[k][j]);
                }
            }
        }
        
        int m; cin >> m;
        path.resize(m);
        for (int i = 0; i < m; ++i) cin >> path[i];
        
        assert(m > 0);
        
        int end = path.back();
        
        int ans = 0;
        for (int i = 0; i + 1 < m; ++i) {
            int cur = path[i];
            int next = path[i + 1];
         
         
            if (d[cur][next] + shortest[next][end] == shortest[cur][end]) { // mi arista esta en el camino mas corto
            } else {
                ans++;
            }
        }
        printf("%d\n", ans);
        
    }

    return 0;
}
