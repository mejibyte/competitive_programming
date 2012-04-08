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

class SumOfPowers {
  public:
  int value(int n, int k);
};

struct Matrix {
    int n;
    vector< vector<int> > data;
    Matrix(){}
    Matrix(int n) : n(n), data(n, vector<int>(n, 0)) {}
};

const int mod = 1000000007;

Matrix operator * (const Matrix &a, const Matrix &b) {
    int n = a.n;
    assert(n == b.n);
    
    Matrix ans(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ans.data[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                ans.data[i][j] += (1LL * a.data[i][k] * b.data[k][j]) % mod;
                ans.data[i][j] %= mod;
            }
        }
    }
    return ans;
}

Matrix pow(const Matrix &m, int e) { // Returns m ** e
    if (e == 1) return m;
    if (e % 2 == 1) return m * pow(m, e - 1);
    Matrix half = pow(m, e / 2);
    return half * half;
}

int SumOfPowers::value(int n, int k) {
    if (n == 1) return 1;
    
    Matrix m(k + 2);
    m.data[k+1][k+1] = 1;
    for (int i = k; i >= 1; --i) {
        for (int j = 0; j <= k + 1; ++j) {
            m.data[i][j] += m.data[i + 1][j];
            m.data[i][j] %= mod;
            if (j + 1 <= k + 1) {
                m.data[i][j] += m.data[i + 1][j + 1];
                m.data[i][j] %= mod;
            }
        }
    }
    
    for (int j = 0; j <= k + 1; ++j) {
        m.data[0][j] = m.data[1][j];
    }
    m.data[0][0] = 1;

    // printf("before power:\n");
    // For(i, 0, k + 2) { For(j, 0, k + 2) printf("%d ", m.data[i][j]); puts(""); }

    m = pow(m, n - 1);
    
    // printf("after powering to %d:\n", n - 1);
    // For(i, 0, k + 2) { For(j, 0, k + 2) printf("%d ", m.data[i][j]); puts(""); }    
    
    int ans = 0;
    for (int j = 0; j <= k + 1; ++j) {
        ans += m.data[0][j];
        ans %= mod;
    }
    return ans;
}

// BEGIN CUT HERE
int main(){
    SumOfPowers sum;
    cout << sum.value(5, 1) << endl;
    cout << sum.value(4, 2) << endl;
    cout << sum.value(13, 5) << endl;
    cout << sum.value(123456789, 1) << endl;
    return 0;
}
// END CUT HERE
