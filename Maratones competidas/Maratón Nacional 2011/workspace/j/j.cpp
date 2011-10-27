// Equipo Poncho, Carriel y Ruana
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
#include <stack>
#include <list>
#include <map>
#include <set>

template <class T> string toStr(const T &x)
{ stringstream s; s << x; return s.str(); }
template <class T> int toInt(const T &x)
{ stringstream s; s << x; int r; s >> r; return r; }

#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define D(x) cout << #x " = " << (x) << endl;

const double EPS = 1e-9;

int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

#define INPUT_FILE "jay"

const int MAXN = 110;
const int MAXB = MAXN * MAXN;
int dp[MAXN][MAXB];

int tiempo[MAXN];
int bolas[MAXN];

int main(){
    freopen(INPUT_FILE ".in", "r", stdin);
    
    int n;
    while (cin >> n) {
        if (n == 0) break;
        int totalBolas = 0;
        For(i, 0, n) {
            cin >> tiempo[i] >> bolas[i];
            totalBolas += bolas[i];
        }
        for (int b = 0; b <= totalBolas; ++b) dp[n][b] = 0;
        for (int i = n - 1; i >= 0; --i) {
            for (int b = 0; b <= totalBolas; ++b) {
                dp[i][b] = dp[i + 1][b + bolas[i]] + tiempo[i];
                if (b > 0) {
                    int option = dp[i + 1][b - 1 + bolas[i]] + tiempo[i] / 2;
                    if (option < dp[i][b]){
                        dp[i][b] = option;
                    }
                }
            } 
        }
        cout << dp[0][0] << endl;
    }
    return 0;

}
