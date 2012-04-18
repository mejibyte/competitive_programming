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

struct BigInt {
    vector<int> d;
    
    BigInt& operator = (int what) {
        if (what == 0) d.assign(1, 0);
        else {
            d.clear();
            while (what > 0) d.push_back(what % 10), what /= 10;
        }
        return *this;
    }
    
    BigInt operator + (const BigInt &that) const {
        BigInt ans;
        int carry = 0;
        for (int i = 0; i < max(d.size(), that.d.size()); ++i) {
            int here = carry;
            if (i < d.size()) here += d[i];
            if (i < that.d.size()) here += that.d[i];
            ans.d.push_back(here % 10);
            carry = here / 10;
        }
        while (carry > 0) ans.d.push_back(carry % 10), carry /= 10;
        return ans;
    }
};

ostream & operator << (ostream& out, const BigInt &x) {
    for (int i = x.d.size() - 1; i >= 0; --i) out << x.d[i];
    return out;
}

typedef BigInt Int;

const int MAXN = 1005;
Int f[MAXN];

int main(){
    f[0] = 1;
    f[1] = 2;
    for (int i = 2; i < MAXN; ++i) {
        f[i] = f[i - 1] + f[i - 2];
        assert(f[i].d.back() > 0);
    }
    
    int n;
    while (cin >> n) {
        cout << f[n] << endl;
    }
    
    return 0;
}