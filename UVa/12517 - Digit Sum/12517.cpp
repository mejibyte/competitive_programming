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

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

map<int, long long> memo;

// Returns the sum of all digits of numbers in range [0, bound].
long long f(int bound) {
    if (bound == 0) return 0;
    if (memo.count(bound)) return memo[bound];
    long long ans = 0;
    for (int place = 0; place <= 9 and place <= bound; ++place) {
        int remain = (bound - place) / 10;
        ans += (remain + 1) * place;
        ans += f(remain);
    }
    return memo[bound] = ans;
}

int main(){
    int low, high;
    while (cin >> low >> high) {
        if (low == 0 and high == 0) break;
        long long ans = f(high) - f(low - 1);
        cout << ans << endl;
    }
    return 0;
}