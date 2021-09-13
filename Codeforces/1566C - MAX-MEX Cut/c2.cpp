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
    for (int at = 0; at < n;) {
        int top = values[0].at(at);
        int bot = values[1].at(at);

        if (top + bot == 1) {
            sum += 2LL;
            at++;
            continue;
        }

        if (top + bot == 2) {
            // Go forward until I see a zero.
            int next = at;
            for (; next < n and values[0][next] == 1 and values[1][next] == 1; next++);
            if (next < n) sum += 2LL;
            at = next + 1;
            continue;
        }

        if (top + bot == 0) {
            sum++;
            at++;
            if (at < n and values[0][at] == 1 and values[1][at] == 1) {
                sum++;
                at++;
            }
            continue;
        }

    }
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
