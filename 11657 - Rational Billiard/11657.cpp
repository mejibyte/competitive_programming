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

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

bool boom(int m, int n, int x0, int y0, int x1, int y1, int p, int q) {
    if (p == 0 or q == 0) {
        int c = p * (y1 - y0) - q * (x1 - x0);
        return (c == 0);
    }
    x0 *= abs(q), x1 *= abs(q), m *= abs(q);
    y0 *= abs(p), y1 *= abs(p), n *= abs(p);
    p /= abs(p);
    q /= abs(q);
    
    int d1 = p * (x1 - x0)       - q * (y1 - y0);
    int d2 = p * (2*m - x1 - x0) - q * (y1 - y0);
    int d3 = p * (x1 - x0)       - q * (2*n - y1 - y0);
    int d4 = p * (2*m - x1 - x0) - q * (2*n - y1 - y0);
    
    int g = __gcd(2*n*q, 2*m*p);

    if (d1 % g == 0) return true;
    if (d2 % g == 0) return true;
    if (d3 % g == 0) return true;
    if (d4 % g == 0) return true;
    return false;
}

int main(){
    int m, n, x0, y0, x1, y1, p, q;
    while (cin >> m >> n >> x0 >> y0 >> x1 >> y1 >> p >> q) {
        if (m == 0 and n == 0 and x0 == 0 and y0 == 0 and x1 == 0 and y1 == 0 and p == 0 and q == 0) break;
        if (boom(m, n, x0, y0, x1, y1, p, q)) {
            puts("HIT");
        } else {
            puts("MISS");
        }
    }
    return 0;
}