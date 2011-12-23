// Andrés Mejía
// Time Limit Exceeded
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

const int MAXN = 505;

int dist[MAXN][MAXN];
int X[MAXN], Y[MAXN];
int a[MAXN];

int monopole(int n) {
    int ans = 1 << 30;
    for(int i = 0; i < n; ++i) {
        int option = 0;
        for(int j = 0; j < n; ++j) {
            option += dist[j][i];
        }
        if (option < ans) ans = option;
    }
    return ans;
}

int pivot;
bool closer(int i, int j) {
    return dist[i][pivot] < dist[j][pivot];
}

int dipole(int n) {
    int ans = (1 << 30);
    
    for(int i = 0; i < n; ++i) {
        pivot = i;
        sort(a, a + n, closer);
        //printf("pivoting on i = %d. Other points are:\n", i + 1);
        //For(k, 0, n) printf("(%d, %d) ", a[k] + 1, dist[i][a[k]]); puts("");
        
        for(int j = i + 1; j < n; ++j) {            
            multiset<int> right;
            right.insert(0);
            right.insert(0);
            
            for(int k = n - 1; k >= 0; --k) {
                
                int l = dist[i][ a[k] ];
                if (k - 1 >= 0) l += dist[i][ a[k - 1] ];
                                
                int r = 0;
                r += *(--right.end());
                r += *right.begin();
                
                int c = dist[i][ a[k] ] + dist[i][j] + *(--right.end());
                
                int option = max(c, max(l, r));
                
                ans = min(ans, option);
                
                right.insert( dist[j][ a[k] ] );
                right.erase(right.begin());
                assert(right.size() == 2);
            }
        }
    }
    return ans;
}

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &X[i], &Y[i]);
        a[i] = i;
    }
    for(int i = 0; i < n; ++i) {
        for(int j = i; j < n; ++j) {
            dist[i][j] = dist[j][i] = abs(X[i] - X[j]) + abs(Y[i] - Y[j]);
        }
    }
    
    //For(i, 0, n) For(j, 0, n) printf("dist[%d][%d] = %d\n", i + 1, j + 1, dist[i][j]);
    
    int ans = min(monopole(n), dipole(n));
    printf("%d\n", ans);
    return 0;
}