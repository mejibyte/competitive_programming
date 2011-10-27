// Equipo Poncho, Carriel y Ruana
// Accepted on UVa
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

int degree[11];

int main(){
    int n, m;
    while (scanf("%d %d", &n, &m) == 2) {
        if (n == 0 and m == 0) break;
        int k; scanf("%d", &k);
        for (int i = 0; i < k + 1; ++i) {
            scanf("%d", &degree[i]);
        }
        int mod = n + 1;
        set<int> ans;
        for (int x = 0; x <= m; x++){
            int y = 0;
            int d = 1;
            for (int i = 0; i < k + 1; ++i) {
                y += (1LL * degree[i] * d) % mod;
                if (y >= mod) y -= mod;
                
                d = (1LL * d * x) % mod;
            }
            ans.insert(y);
        }
        printf("%d\n", (int)ans.size());
    }
    return 0;

}
