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

bitset<MAXL> hits[2][2*MAXN];
int number_of_hits[2][2*MAXN];

bool inline check_up(int x0, int y0, int a, int b) {
    return ((x0 - a) - (y0 - b)) % G == 0;
}

bool inline check_down(int x0, int y0, int a, int b) {
    return ((x0 - a) + (y0 - b)) % G == 0;
}

bool more_hits_first(int i, int j) {
    return number_of_hits[0][i] + number_of_hits[1][i] > number_of_hits[0][j] + number_of_hits[1][j];
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

        bool hit_up = false, hit_down = false;
        for (int j = 0; j < i; ++j) {
            int x0 = i, y0 = 0, x = sx[j], y = sy[j];
            hit_up |= (check_up(x0, y0, x, y) or check_up(x0, y0, -x, y) or check_up(x0, y0, x, -y) or check_up(x0, y0, -x, -y));
            hit_down |= (check_down(x0, y0, x, y) or check_down(x0, y0, -x, y) or check_down(x0, y0, x, -y) or check_down(x0, y0, -x, -y));
        }
        if (!hit_up or !hit_down) {
            sx.push_back(i);
            sy.push_back(0);
        }
    }
    
    for (int i = 0; i <= min(C, R); ++i) {
        bool hit_up = false, hit_down = false;
        for (int j = 0; j < i; ++j) {
            int x0 = 0, y0 = i, x = sx[j], y = sy[j];
            hit_up |= (check_up(x0, y0, x, y) or check_up(x0, y0, -x, y) or check_up(x0, y0, x, -y) or check_up(x0, y0, -x, -y));
            hit_down |= (check_down(x0, y0, x, y) or check_down(x0, y0, -x, y) or check_down(x0, y0, x, -y) or check_down(x0, y0, -x, -y));
        }
        if (!hit_up or !hit_down) {
            sx.push_back(0);
            sy.push_back(i);
        }
    }
    
    int n = sx.size();
        
    for (int i = 0; i < n; ++i) {
        int x0 = sx[i], y0 = sy[i];
        for (int j = 0; j < L; ++j) {
            int x = X[j], y = Y[j];
            if (check_up(x0, y0, x, y) or check_up(x0, y0, -x, y) or check_up(x0, y0, x, -y) or check_up(x0, y0, -x, -y)) {
                hits[0][i][j] = true;
                number_of_hits[0][i]++;
            }

            if (check_down(x0, y0, x, y) or check_down(x0, y0, -x, y) or check_down(x0, y0, x, -y) or check_down(x0, y0, -x, -y)) {
                hits[1][i][j] = true;
                number_of_hits[1][i]++;
            }
        }
    }
    //D(n); D(L);
    //D(n * L);
    
    //D(1.0 * clock() / CLOCKS_PER_SEC);
    
    vector<int> sorted(n);
    for (int i = 0; i < n; ++i) sorted[i] = i;
    sort(sorted.begin(), sorted.end(), more_hits_first);
    
    int ans = 0;
    for (int p = 0; p < n; ++p) {
        int i = sorted[p];
        for (int q = p + 1; q < n; ++q) {
            int j = sorted[q];
            if ((sx[i] + sy[i] - sx[j] - sy[j]) % 2 == 0) {
                if (number_of_hits[0][i] + number_of_hits[1][j] < ans) continue;
                bitset<MAXL> both = hits[0][i] | hits[0][j];
                int option = both.count();
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