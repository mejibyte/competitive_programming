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

#define minimize(x, y) if ((y) < (x)) (x) = (y)

int W, L;
int X[18], Y[18];

double dp[18][1 << 18];
double dist[18][18];

double euclidean(int x1, int y1,   int x2, int y2) {
    int dx = x1 - x2;
    int dy = y1 - y2;
    return sqrt(dx * dx + dy * dy);
}

double closest(int i, int j) {
    // double ans = euclidean(X[i], Y[i],    X[j], -Y[j] );
    //     minimize( ans, euclidean(X[i], Y[i],  2 * W - X[j], Y[j] ) );
    //     minimize( ans, euclidean(X[i], Y[i],  X[j], 2 * L - Y[j] ) );
    //     minimize( ans, euclidean(X[i], Y[i],  -X[j], Y[j] ) );
    //     
    
    int sx = X[i] + X[j];
    int sy = Y[i] + Y[j];
    double ans = min(
        hypot(X[i] - X[j], min(sy, 2 * L - sy)),
        hypot(Y[i] - Y[j], min(sx, 2 * W - sx))
    );
    
    return ans;
}

double finish(int i) {
    double ans = X[i];
    minimize(ans, Y[i]);
    minimize(ans, W - X[i]);
    minimize(ans, L - Y[i]);
    return ans;
}

int main(){
    scanf("%d %d", &W, &L);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", X + i, Y + i);
    }
    int xr, yr;
    scanf("%d %d", &xr, &yr);
    for(int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            dist[i][j] = dist[j][i] = closest(i, j);
        }
        dist[i][i] = 0.0;
    }

    for (int i = 0; i < n; ++i) {
        dp[i][(1 << n) - 1] = finish(i);
    }

    for (int mask = (1 << n) - 2; mask > 0; --mask) {
        for (int i = 0; i < n; ++i) {
            if ( (mask & (1 << i) ) == 0) continue;
            
            dp[i][mask] = 1e100;
            
            for (int j = 0; j < n; ++j) {
                if ( mask & (1 << j) ) continue;
                assert(i != j);
                
                int nextMask = mask | (1 << j);
                
                minimize( dp[i][mask], dp[j][nextMask] + dist[i][j] );
                
            }
        }
    }
    
    double ans = 1e100;
    for (int i = 0; i < n; ++i) {
        minimize( ans, dp[i][1 << i] + hypot(X[i] - xr, Y[i] - yr) );
    }

    printf("%.14lf\n", ans);

    return 0;
}