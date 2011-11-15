/*
  LANG: C++
  PROB: milk
*/
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

struct farmer {
    int price, avail;
    bool operator < (const farmer &t) const {
        return price < t.price;
    }
};

farmer v[5000];

int main(){
    freopen("milk.in", "r", stdin);
    freopen("milk.out", "w", stdout);
    
    int n, m;
    while (scanf("%d %d", &n, &m) == 2) {
        for (int i = 0; i < m; ++i) scanf("%d %d", &v[i].price, &v[i].avail);
        sort(v, v + m);
        int ans = 0;
        for (int i = 0; n > 0; ++i) {
            int buy = min(n, v[i].avail);
            ans += v[i].price * buy;
            n -= buy;
        }
        printf("%d\n", ans);
    }
    return 0;
}