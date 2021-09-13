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

void solve() {
    string s;
    cin >> s;

    int blocks_of_zeroes = 0;

    int n = s.size();
    for (int i = 0; i < n; ) {
        if (s[i] == '1') i++;
        else {
            int j = i;
            while (j < n and s[j] == '0') j++;
            blocks_of_zeroes++;
            i = j;
        }
    }

    if (blocks_of_zeroes == 0) {
        cout << 0 << endl;
    } else if (blocks_of_zeroes == 1) {
        cout << 1 << endl;
    } else {
        cout << 2 << endl;
    }
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
