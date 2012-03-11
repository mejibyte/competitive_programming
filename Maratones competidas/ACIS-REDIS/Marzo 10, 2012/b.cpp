using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
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
#include <map>
#include <set>

#define For (i, a, b) for (int i = (a); i < (b); i++)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); x++)
#define D(x) cout << #x " = " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS){
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

map< pair<int, int>, double > memo;

double f(int n, int k) {
    if (n < 0 or k < 0 or k > n) return 0.0;
    if (k == 0) return 1;
    if (k == n) return 1;
    
    pair<int, int> key(n, k);
    if (memo.count(key)) return memo[key];
    
    double ans = (f(n - 1, k - 1) * f(n - 1, k) + 1) / f(n - 2, k - 1);
    memo[key] = ans;
    return ans;
}

int brute(int n, int m) {
    double ans = f(n, m);
    ans = floor(ans + 0.5);
    return (int)ans;
}

long long solve(long long n, long long m) {        
    if (n < 0 or m < 0 or m > n) {
        return 0;
    }
    
    return (n - m) * m + 1;
}


void check() {
    for (int i = 0; i <= 1000; ++i) {
        for (int j = 0; j <= 1000; ++j) {
            assert(brute(i, j) == solve(i, j));
        }
    }
}


int main() {
    //check();
    
    int casos; cin >> casos;
    while (casos--) {
        int id, n, m; cin >> id >> n >> m;
        
        cout << id << " " << solve(n, m) << endl;
        
    }
    return 0;
}
