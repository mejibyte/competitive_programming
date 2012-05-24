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

const int MAXL = 10005, MAXN = 1605;
int X[MAXL], Y[MAXL];

//bitset<MAXL> hits[2][MAXL];

vector<int> hits[2][2*MAXN];

bool check_up(int x0, int y0, int a, int b) {
    return ((x0 - a) - (y0 - b)) % G == 0;
}

bool check_down(int x0, int y0, int a, int b) {
    return ((x0 - a) + (y0 - b)) % G == 0;
}

int main(){
    ios::sync_with_stdio(false);
    
    cin >> R >> C >> L;
    
    R = R - 1;
    C = C - 1;
    
    G = __gcd(2*R, 2*C);
    
    for (int i = 0; i < L; ++i) {
        cin >> X[i] >> Y[i];
    }
    
    vector<int> sx, sy;
    for (int i = 0; i <= min(C, R); ++i) {
        sx.push_back(i);
        sy.push_back(0);
    }
    
    for (int i = 0; i <= min(C, R); ++i) {
        sx.push_back(0);
        sy.push_back(i);
    }
    
    int n = sx.size();
    
    for (int i = 0; i < n; ++i) {
        int x0 = sx[i], y0 = sy[i];
        for (int j = 0; j < L; ++j) {
            int x = X[j], y = Y[j];
            if (check_up(x0, y0, x, y) or check_up(x0, y0, -x, y) or check_up(x0, y0, x, -y) or check_up(x0, y0, -x, -y)) {
                hits[0][i].push_back(j);
            }
            if (check_down(x0, y0, x, y) or check_down(x0, y0, -x, y) or check_down(x0, y0, x, -y) or check_down(x0, y0, -x, -y)) {
                hits[1][i].push_back(j);
            }
        }
    }
    //D(n); D(L);
    //D(n * L);
    
    //D(1.0 * clock() / CLOCKS_PER_SEC);
    
    
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if ((sx[i] + sy[i] - sx[j] - sy[j]) % 2 == 0) {
                
                if (hits[0][i].size() + hits[1][j].size() < ans) continue;
                //D(hits[0][i].size() + hits[1][j].size());
                
                int option = 0, p, q;
                for (p = 0, q = 0; p < hits[0][i].size() and q < hits[1][j].size(); ) {
                    if (hits[0][i][p] < hits[1][j][q]) {
                        p++;
                    } else if (hits[0][i][p] > hits[1][j][q]) {
                        q++;
                    } else {
                        p++;
                        q++;
                    }
                    option++;
                }
                while (p < hits[0][i].size()) option++, p++;
                while (q < hits[1][j].size()) option++, q++;
                //bitset<MAXL> both = hits[0][i] | hits[1][j];
                //int option = both.count();
                if (option > ans) {
                    ans = option;
                }
            }
        }
    }
    
    //D(1.0 * clock() / CLOCKS_PER_SEC);
        
    cout << ans;
    return 0;
}