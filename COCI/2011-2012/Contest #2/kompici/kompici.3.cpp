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

int times[1 << 10];

int main(){
    long long ans = 0;
    int n;
    scanf("%d", &n);
    
    for (int i = 0; i < n; ++i) {
        long long x; scanf("%lld", &x);
        
        int mask = 0;
        while (x > 0) {
            mask |= 1 << (x % 10);
            x /= 10;
        }

        times[mask]++;
    }
    for (int i = 0; i < 1024; ++i) {
        for (int j = i + 1; j < 1024; ++j) {
            if ((i & j) == 0) continue;
            ans += (long long)times[i] * times[j];
        }
        ans += ( (long long)times[i] * (times[i] - 1) ) >> 1;
    }
    printf("%lld\n", ans);
    return 0;
}