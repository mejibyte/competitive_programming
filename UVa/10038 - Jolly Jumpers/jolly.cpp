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

#include <bitset>

const int MAXN = 3005;
bitset<MAXN> seen;

int main(){
    int n;
    while (cin >> n) {
        seen.reset();
        int u; cin >> u;
        for (int i = 1; i < n; ++i) {
            int v; cin >> v;
            int diff = abs(u - v);
            if (diff < MAXN) seen[diff] = true;
            u = v;
        }
        bool jolly = true;
        for (int i = 1; i <= n - 1; ++i) {
            jolly &= seen[i];
        }
        cout << (jolly ? "Jolly" : "Not jolly") << endl;
    }
    return 0;
}