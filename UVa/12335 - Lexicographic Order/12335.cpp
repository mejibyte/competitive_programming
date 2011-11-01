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

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

long long factorial(int i) {
    long long ans = 1;
    for (long long k = 2; k <= i; ++k) ans *= k;
    return ans;
}

void permute(int i, vector<int> &base, long long k) {
    int n = base.size() - i;
    for (int p = 1; p <= n; ++p) {
        if (p * factorial(n - 1) >= k) {
            swap(base[i], base[i + p - 1]);
            if (i + 1 < base.size()) {
                sort(base.begin() + i + 1, base.end());
                permute(i + 1, base, k - (p - 1) * factorial(n - 1));
            }
            break;
        }
    }
}

int main(){
    int T; cin >> T;
    for (int Case = 1; Case <= T; ++Case) {
        string s; long long k;
        cin >> s >> k;
        int n = s.size();
        
        vector<int> base(n);
        for (int i = 0; i < n; ++i) {
            base[i] = i;
        }
        
        permute(0, base, k);
        
        string ans(s.size(), ' ');
        for (int i = 0; i < s.size(); ++i) {
            ans[base[i]] = s[i];
        }
        printf("Case %d: %s\n", Case, ans.c_str());
    }
    return 0;
}