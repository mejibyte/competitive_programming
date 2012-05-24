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

const int mod = 1000000007;
const int S = 3;

struct Matrix {
    int d[S][S];
    
    Matrix operator * (const Matrix &b) const {
        Matrix ans;
        memset(ans.d, 0, sizeof ans.d);
        for (int i = 0; i < S; ++i) {
            for (int j = 0; j < S; ++j) {
                for (int k = 0; k < S; ++k) {
                    ans.d[i][j] += (1LL * d[i][k] * b.d[k][j]) % mod;
                    ans.d[i][j] %= mod;
                }
            }
        }
        return ans;
    }
};

Matrix pow(const Matrix &m, int e) {
    assert(e > 0);
    if (e == 1) return m;
    
    if (e & 1) {
        return m * pow(m, e - 1);
    } else {
        Matrix half = pow(m, e / 2);
        return half * half;
    }
}


int get_sum(int n) {
    if (n < 0) return 0;
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    int magic[3][3] = {{0, 1, 0},
                       {1, 1, 0},
                       {0, 1, 1}};
                       
                       
    // magic * [F_i, F_i+1, S_i] gives [F_i+1, F_i+2, S_i+1], where F_i is the i-th Fibonacci number and S_i is the sum of S_0 upto S_i.
    Matrix p;
    memcpy(p.d, magic, sizeof magic);
    
    p = pow(p, n);
    
    return p.d[2][1];
}

int main(){
    int runs; cin >> runs;
    while (runs--) {
        int a, b;
        cin >> a >> b;
        int ans = get_sum(b) - get_sum(a - 1);
        if (ans < 0) ans += mod;
        cout << ans << endl;
    }
    return 0;
}