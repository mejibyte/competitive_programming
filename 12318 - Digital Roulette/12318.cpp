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

int main(){
    int n, m;
    while (cin >> n >> m) {
        if (n == 0 and m == 0) break;
        int k; cin >> k;
        vector<long long> grad(k + 1);
        for (int i = 0; i < k + 1; ++i) {
            cin >> grad[i];
        }
        long long mod = n + 1;
        //assert(grad.size() == k + 1);
        set<long long> ans;
        for (long long x = 0; x <= m; x++){
            long long y = 0;
            long long d = 1;
            for (int i = 0; i < grad.size(); ++i) {
                //printf("   y = y + %d\n", grad[i] * d);
                y += ((grad[i] % mod) * d) % mod;
                y %= mod;
                d = (d * (x % mod)) % mod;
            }
            ans.insert(y % mod);
            //printf("added %d\n", y % mod);        
        }
        cout << ans.size() << endl;
    }
    return 0;

}
