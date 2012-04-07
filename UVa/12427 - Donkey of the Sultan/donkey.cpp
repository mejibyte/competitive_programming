// Andrés Mejía

// I haven't been able to test this submission because UVa sucks and it will ignore my submissions.

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

// Returns the number of even integers in range [a, b].
long long between(long long a, long long b) {
    return b / 2 - (a + 1) / 2 + 1;
}

int main(){
    int runs; cin >> runs;
    for (int run = 1; run <= runs; ++run) {
        long long a1, a2, b1, b2, c1, c2;
        cin >> a1 >> a2 >> b1 >> b2 >> c1 >> c2;
        long long ans = between(a1, a2) * (b2 - b1 + 1) * between(c1, c2);
        cout << "Case " << run << ": " << ans << endl;
    }
    return 0;
}