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

char memo[1000005];

int main(){
    ios::sync_with_stdio(false);
    int n;
    unsigned long long f = 1;
    for (int i = 1; i <= 1000000; ++i) {
        f *= i;
        while (f > 0 and f % 10 == 0) f /= 10;
        memo[i] = f % 10;
        f %= 1000000000LL;
    }
    while (scanf("%d", &n) == 1) {
        printf("%5d -> %d\n", n, (int)memo[n]);
    }
    return 0;
}