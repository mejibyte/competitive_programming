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

#define D(x) cout << #x " is " << (x) << endl

int gcd(int a, int b) {
    return abs(b == 0 ? a : gcd(b, a % b));
}

const int MAXN = 1005;
int a[MAXN];

int main() {
    while (true) {
        int n = 0;
        for (int x; cin >> x and x != 0; ) {
            a[n++] = x;
        }
        if (n == 0) break;
        
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                ans = gcd(ans, a[i] - a[j]);
            }
        }
        assert(ans > 0); // if ans == 0 it's because all numbers are equal.
        cout << ans << endl;
    }
    return 0;
}