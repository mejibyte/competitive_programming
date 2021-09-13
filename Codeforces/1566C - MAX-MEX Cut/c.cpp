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
using namespace std;

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cerr << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

vector<int> values[2];

int64_t mex(int from, int to) {
    set<int> got;
    for (int i = from; i <= to; ++i) {
        got.insert(values[0][i]);
        got.insert(values[1][i]);
    }
    for (int i = 0; i <= 2; i++) {
        if (got.count(i) == 0) return i;
    }
    assert(false);
}

void solve() {
    int n;
    cin >> n;

    string s[2];
    cin >> s[0];
    cin >> s[1];
    for (int d = 0; d < 2; d++) {
        values[d].resize(n);
        for (int i = 0; i < n; i++) {
            values[d][i] = s[d][i] - '0';
        }
    }

    int64_t sum = 0;
    int from = 0;
    for (int at = 0; at < n; at++) {
        int top = values[0][at];
        int bot = values[1][at];

        if (top + bot == 1) {
            printf("(01 or 10): from=%d, at=%d, mex=%d\n", from, at, mex(from, at));
            sum += mex(from, at); // has to be 2
            from = at + 1;
            continue;
        }
        if (top + bot == 2) {
            printf("(11): at=%d, continue\n", at);
            continue;
        }

        // 0 0
        int m = mex(from, at);
        if (m >= 2) {
            printf("(00): from=%d, at=%d, mex=%d\n", from, at, m);
            sum += m;
            from = at + 1;
            continue;
        }
    }
    printf("end: from=%d, n-1=%d, mex=%d\n", from, n-1, mex(from, n-1));
    sum += mex(from, n-1);
    cout << sum << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
