// Andrés Mejía
// UVa 756 - Biorhythms
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

// Assumes gcd(a, n) == 1 and a > 0.
long long modular_inverse(long long a, long long n) {
    long long i = n, v = 0, d = 1;
    while (a > 0) {
        long long t = i / a, x = a;
        a = i % x;
        i = x;
        x = d;
        d = v - t * x;
        v = x;
    }
    v %= n;
    if (v < 0) v += n;
    return v;
}


int chinese_remainder(vector<int> a, vector<int> b) {
    assert(a.size() == b.size());
    int n = a.size();
    // it is assumed that b contains pairwise relatively prime integers
    int B = 1;
    for (int i = 0; i < n; ++i) {
        a[i] %= b[i];
        B *= b[i]; // Careful with overflow here!
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int m = B / b[i];
        int c = m * modular_inverse(m, b[i]); // Careful with overflow here!
        ans += (a[i] * c) % B; // Careful with overflow here!
        if (ans >= B) ans %= B;
    }
    return ans;
}

int main(){
    int run = 1;
    vector<int> b;
    b.push_back(23);
    b.push_back(28);
    b.push_back(33);
    int x, y, z, d;
    while (cin >> x >> y >> z >> d) {
        if (x == -1 and y == -1 and z == -1 and d == -1) break;
        x %= 23;
        y %= 28;
        z %= 33;
        vector<int> a;
        a.push_back(x);
        a.push_back(y);
        a.push_back(z);
        
        int ans = chinese_remainder(a, b);
        while (ans <= d) ans += 23 * 28 * 33;
        printf("Case %d: the next triple peak occurs in %d days.\n", run++, ans - d);
    }
    
    return 0;
}