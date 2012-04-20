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

int mod;

vector<int> times(const vector<int> &a, const vector<int> &b) {
    vector<int> ans(4, 0);
    ans[0] = (1LL * a[0] * b[0]) % mod + (1LL * a[1] * b[2]) % mod;
    ans[1] = (1LL * a[0] * b[1]) % mod + (1LL * a[1] * b[3]) % mod;
    ans[2] = (1LL * a[2] * b[0]) % mod + (1LL * a[3] * b[2]) % mod;
    ans[3] = (1LL * a[2] * b[1]) % mod + (1LL * a[3] * b[3]) % mod;
    ans[0] %= mod;
    ans[1] %= mod;
    ans[2] %= mod;
    ans[3] %= mod;
    return ans;
}

vector<int> pow(const vector<int> &what, int e) {
    if (e == 1) return what;
    if (e & 1) return times(what, pow(what, e - 1));
    vector<int> h = pow(what, e / 2);
    return times(h, h);
}

void solve(int n) {
    vector<int> magic(4, 1);
    magic[0] = 0;
    vector<int> ans = pow(magic, n);
    printf("%d\n", ans[1]);
}

int main(){
    ios::sync_with_stdio(false);
    int n, m;
    while (cin >> n >> m) {
        mod = (1 << m);
        if (n == 0) puts("0");
        else solve(n);
    }
    return 0;
}