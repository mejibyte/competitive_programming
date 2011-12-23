// Andrés Mejía
// Accepted.

// Uses ideas presented in this paper: http://dx.doi.org/10.1145/73833.73864
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

#define dassert(condition) //assert

const int MAXN = 505;

int dist[MAXN][MAXN];
int X[MAXN], Y[MAXN];
int a[MAXN];

int pivot;
bool closer(int i, int j) {
    return dist[i][pivot] < dist[j][pivot];
}

inline int max3(int a, int b, int c) {
    if (c >= a and c >= b) return c;
    if (b >= a and b >= c) return b;
    return a;
}

int dipole(int n) {
    int ans = (1 << 30);
    
    for(int i = 0; i < n; ++i) {
        pivot = i;
        sort(a, a + n, closer);

        for(int j = i + 1; j < n; ++j) {
            int r1 = 0, r2 = 0;
            
            for(int k = n - 1; k >= 0; --k) {
                
                int l = dist[i][ a[k] ];
                if (k - 1 >= 0) l += dist[i][ a[k - 1] ];

                int r = 0;
                r += r1;
                r += r2;
                
                int c = dist[i][ a[k] ] + dist[i][j] + r2;
                
                // { l == longest diameter on the left subtree (the subtree rooted at i) }
                // { r == longest diameter on the right subtree (the subtree rooted at j) }
                // { c == longest diameter that crosses the edge (i, j) from the left subtree to the right subtree }
                
                int option = max3(c, l, r);
                
                if (option < ans) ans = option;
                
                // We are inserting next in the right side, so make sure to update
                // r1 and r2 accordingly so they hold the biggest two values inserted
                // so far in the right side.
                int next = dist[j][ a[k] ];
                if (next >= r2) {
                    r1 = r2, r2 = next;
                } else if (next >= r1) {
                    r1 = next;
                } else {
                    dassert(next < r1 and next < r2);
                }
                dassert(r1 <= r2);
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
    
    int ans = dipole(n);
    printf("%d\n", ans);
    return 0;
}