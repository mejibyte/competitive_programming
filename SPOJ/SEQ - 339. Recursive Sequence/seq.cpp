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

const int mod = 1000000000;

struct Matrix {
    int size;
    vector< vector<int> > data;
    Matrix(int k) :size(k), data(k, vector<int>(k, 0)) { }
};

Matrix operator * (const Matrix &a, const Matrix &b) {
    Matrix ans(a.size);
    for (int i = 0; i < a.size; ++i) {
        for (int j = 0; j < a.size; ++j) {
            for (int k = 0; k < a.size; ++k) {
                ans.data[i][j] += (1LL * a.data[i][k] * b.data[k][j]) % mod;
                ans.data[i][j] %= mod;
            }
        }
    }
    return ans;
}

Matrix pow(const Matrix &m, int n) {
    if (n == 1) return m;
    if (n % 2 == 1) return m * pow(m, n - 1);
    Matrix half = pow(m, n / 2);
    return half * half;
}

int main(){
    int C; cin >> C;
    while (C--) {
        int k; cin >> k;
        vector<int> b(k);
        for (int i = 0; i < k; ++i) cin >> b[i];
        Matrix m(k);
        for (int i = 0; i < k - 1; ++i) {
            m.data[i][i + 1] = 1;
        }
        for (int j = k - 1; j >= 0; --j) {
            cin >> m.data[k - 1][j];
        }
        int n; cin >> n;
        if (n > 1) m = pow(m, n - 1);

        int ans = 0;
        for (int i = 0; i < k; ++i) {
            ans += (1LL * m.data[0][i] * b[i]) % mod;
            ans %= mod;
        }
        printf("%d\n", ans);
    }
    return 0;
}