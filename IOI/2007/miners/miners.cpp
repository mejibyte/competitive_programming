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

const int MAXN = 100005;

char food[MAXN];
int dp[2][256];

int extra(int a, int b, int c) {
    assert(c != 0);
    assert(a == 0 or b != 0);
    if (a == 0) {
        if (b == 0) return 1;
        else return 1 + (b != c);
    }
    assert(a != 0 and b != 0 and c != 0);
    return 1 + (b != c) + (a != b and a != c);
}

int main(){
    int n; scanf("%d ", &n);
    gets(food);
    
    const int impossible = -1000000000;
    for (int i = 0; i < 256; ++i) {
        dp[0][i] = impossible;
    }
    dp[0][0] = 0;
    
    // D(extra(0, 0, 1));
    // D(extra(3, 2, 1));
    // D(extra(2, 3, 2));
    // D(extra(2, 1, 1));
    // D(extra(0, 2, 1));
    // D(extra(0, 2, 2));
    
    int cur = 0, next = 1, option;
    
    for (int i = 0; i < n; ++i) {
        int value = food[i] == 'M' ? 1 : food[i] == 'F' ? 2 : 3;

        for (int m = 0; m < 256; ++m) {
            dp[next][m] = impossible;
        }

        for (int a = 0; a < 16; ++a) {
//            if (a and (a & 4) == 0) continue;
            for (int b = 0; b < 16; ++b) {
//                if (b and (b & 4) == 0) continue;
                int here = dp[cur][(a << 4) + b];
                
                if (here == impossible) continue;
                
                // put it on a
                option = here + extra(a >> 2, a & 3, value);
                int next_a = ((a << 2) & 15) + value;
                if (option > dp[next][(next_a << 4) + b]) {
                    dp[next][(next_a << 4) + b] = option;
                }
                
                // put it on b
                option = here + extra(b >> 2, b & 3, value);
                int next_b = ((b << 2) & 15) + value;
                if (option > dp[next][(a << 4) + next_b]) {
                    dp[next][(a << 4) + next_b] = option;
                }
                
            }
        }
        cur ^= 1, next ^= 1;
    }
    
    int ans = impossible;
    for (int i = 0; i < 256; ++i) {
        if (dp[n & 1][i] > ans) ans = dp[n & 1][i];
    }
    cout << ans << endl;
    return 0;
}