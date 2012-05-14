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

int magic[2][2] = {{3, 1}, {1, 3}};

struct Matrix {
    int d[2][2];
};

const int mod = 1000000007;

Matrix product(const Matrix &a, const Matrix &b) {
    Matrix ans;
    memset(ans.d, 0, sizeof ans.d);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 2; ++k) {
                ans.d[i][j] += (1LL * a.d[i][k] * b.d[k][j]) % mod;
                ans.d[i][j] %= mod;
            }
    return ans;
}

    Matrix power(const Matrix &a, long long e) {
    if (e == 1) return a;
    if (e & 1) return product(a, power(a, e - 1));
    Matrix half = power(a, e / 2);
    return product(half, half);
}


int main(){
    long long n;
    cin >> n;
    
    if (n == 0) {
        cout << 1 << endl;
        return 0;
    }
    
    Matrix t;
    t.d[0][0] = 3; t.d[0][1] = 1;
    t.d[1][0] = 1; t.d[1][1] = 3;
    
    Matrix bang = power(t, n);
    
    cout << bang.d[0][0] << endl;
    
    return 0;
}