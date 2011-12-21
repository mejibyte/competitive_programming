using namespace std;
#include <algorithm>
#include <iostream>
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
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>

#define For(i, a, b) for (int i = (a); i < (b); ++i)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define D(x) cout << #x " = " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

#define INPUT_FILE "kitchen"

const int MAXN = 18;

int W, L, N;

double dist[MAXN][MAXN];
int X[MAXN], Y[MAXN];

bool been[MAXN][1 << MAXN];
double memo[MAXN][1 << MAXN];

double bordeMasCercano(int cur) {
    double ans = 1e100, option;
    
    option = X[cur];
    if (option < ans) ans = option;
    
    option = Y[cur];
    if (option < ans) ans = option;

    option = L - Y[cur];
    if (option < ans) ans = option;

    option = W - X[cur];
    if (option < ans) ans = option;
    
    return ans;
}


 double f(int cur, int seen) {  
    if (seen == (1 << N) - 1) {
        return bordeMasCercano(cur);
    }
    if (been[cur][seen]) return memo[cur][seen];
    
     double ans = 1e100;
    for (int next = 0; next < N; ++next) {
        if (seen & (1 << next)) continue;
        
        int nextSeen = seen | (1 << next);
        
        double option = dist[cur][next] + f(next, nextSeen);
        
        if (option < ans) ans = option;
        
    }
    
    memo[cur][seen] = ans;
    been[cur][seen] = true;
    return ans;
    
}

double closest(int i, int j) {
    double ans = 1e100, option;
    
    option = hypot(X[i] - X[j], Y[i] + Y[j]);
    if (option < ans) ans = option;
    
    option = hypot(X[i] - X[j], Y[i] + Y[j] - 2 * L);
    if (option < ans) ans = option;

    option = hypot(X[i] + X[j], Y[i] - Y[j]);
    if (option < ans) ans = option;

    option = hypot(X[i] + X[j] - 2 * W, Y[i] - Y[j]);
    if (option < ans) ans = option;
    
    return ans;
        
}

int main() {
    //freopen(INPUT_FILE ".in", "r", stdin);
    
    while (scanf("%d %d", &W, &L) == 2) {
        if (W == 0 and L == 0) break;
        
        int n; scanf("%d", &n);
        N = n;
        
        for (int i = 0; i < n; ++i) scanf("%d %d", &X[i], &Y[i]);
        int xr, yr;
        scanf("%d %d", &xr, &yr);
        
        For(i, 0, n) {
            For(j, i + 1, n) {
                dist[i][j] = dist[j][i] = closest(i, j);
            }
            dist[i][i] = 0;
        }
        
        For(i, 0, n) For(j, 0, (1 << n)) been[i][j] = false;
        
        double ans = 1e100;
        For(i, 0, n) {
            double option = hypot(xr - X[i], yr - Y[i]) + f(i, 1 << i);
            if (option < ans) ans = option;
        }
        printf("%.10lf\n", (double)ans);
    }
    
    
    return 0;
}
