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

void binary(int x) {
    string s = "";
    do {
        s = char('0' + (x & 1)) + s;
        x >>= 1;
    } while (x > 0);
    puts(s.c_str());
}

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

        for(int m = mask; m > 0; m = (m - 1) & mask){
            int p = __builtin_parity(m);
            
            if (p == 1) {
                ans += times[m];
            } else {
                ans -= times[m];
            }
        }

        for(int m = mask; m > 0; m = (m - 1) & mask){
            times[m]++;
        }
    }
    printf("%lld\n", ans);
    return 0;
}