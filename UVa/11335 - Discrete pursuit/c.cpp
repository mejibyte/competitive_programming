// Andrés Mejía
// Accepted
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

int f(int s, int v) {
    for (int k = 1; ; ++k) {
        if (1LL * k * (k + 1) / 2 >= s + k * v) return k;
    }
    assert(false);
}

int main(){
    int a, u, v;
    while (cin >> a >> u >> v) {
        if (a == 0) {
            cout << 0 << endl;
            continue;
        }
        
        int ans = max(f(a, u), f(0, v));
        cout << ans << endl;
    }
    
    return 0;
}