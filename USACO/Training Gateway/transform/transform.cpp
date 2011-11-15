/*
    TASK: transform
    LANG: C++
*/
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

vector<string> rotate(vector<string> a) {
    int n = a.size();
    vector<string> ans(n, string(n, '*'));
    For(i, 0, n) {
        For(j, 0, n) {
            ans[j][n - 1 - i] = a[i][j];
        }
    }
    return ans;
}

vector<string> reflect(vector<string> a) {
    int n = a.size();
    vector<string> ans(n, string(n, '*'));
    For(i, 0, n) {
        For(j, 0, n) {
            ans[i][n - 1 - j] = a[i][j];
        }
    }
    return ans;
}

int solve(vector<string> &a, vector<string> &b) {
    if (rotate(a) == b) return 1;
    if (rotate(rotate(a)) == b) return 2;
    if (rotate(rotate(rotate(a))) == b) return 3;
    if (reflect(a) == b) return 4;
    {
        vector<string> r = reflect(a);
        if (rotate(r) == b || rotate(rotate(r)) == b || rotate(rotate(rotate(r))) == b) return 5;
    }
    if (a == b) return 6;
    return 7;
}

int main(){
    #ifndef LOCAL
    freopen("transform.in", "r", stdin);
    freopen("transform.out", "w", stdout);
    #endif
    
    int n;
    cin >> n;
    string s; getline(cin, s);
    vector<string> a, b;
    for (int i = 0; i < n; ++i) {
        getline(cin, s);
        a.push_back(s);
    }
    for (int i = 0; i < n; ++i) {
        getline(cin, s);
        b.push_back(s);
    }
    printf("%d\n", solve(a, b));
    return 0;
}