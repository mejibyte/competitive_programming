// Andrés Mejía

// Gives correct answers, but times out.

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
#include <bitset>
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

int R, C, L, G;

const int MAXL = 10005;
int X[MAXL], Y[MAXL];

bitset<MAXL> hits[2][MAXL];

bool check_up(int x0, int y0, int a, int b) {
    return ((x0 - a) - (y0 - b)) % G == 0;
}

bool check_down(int x0, int y0, int a, int b) {
    return ((x0 - a) + (y0 - b)) % G == 0;
}

int main(){
    cin >> R >> C >> L;
    
    R = R - 1;
    C = C - 1;
    
    G = __gcd(2*R, 2*C);
    
    for (int i = 0; i < L; ++i) {
        cin >> X[i] >> Y[i];
    }
    
    // direction (+1,+1)
    for (int i = 0; i < L; ++i) {
        int x0 = X[i], y0 = Y[i];
        for (int j = 0; j < L; ++j) {
            int x = X[j], y = Y[j];
            hits[0][i][j] = check_up(x0, y0, x, y) or check_up(x0, y0, -x, y) or check_up(x0, y0, x, -y) or check_up(x0, y0, -x, -y);
            //printf("From (%d, %d) in direction up hits light at (%d, %d)? %d\n", x0, y0, x, y, (int)hits[0][i][j]);
        }
    }

    // direction (+1,-1)
    for (int i = 0; i < L; ++i) {
        int x0 = X[i], y0 = Y[i];
        for (int j = 0; j < L; ++j) {
            int x = X[j], y = Y[j];
            hits[1][i][j] = check_down(x0, y0, x, y) or check_down(x0, y0, -x, y) or check_down(x0, y0, x, -y) or check_down(x0, y0, -x, -y);
            //printf("From (%d, %d) in direction down hits light at (%d, %d)? %d\n", x0, y0, x, y, (int)hits[1][i][j]);
        }
    }

    int ans = 0;
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < L; ++j) {
            if ((X[i] + Y[i] - X[j] - Y[j]) % 2 == 0) {
                bitset<MAXL> both = hits[0][i] | hits[1][j];
                int option = both.count();
                if (option > ans) {
                    ans = option;
                }
            }
        }
    }
    cout << ans;
    return 0;
}