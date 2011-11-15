/*
    TASK: dualpal
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

string toBase(int x, int b) {
    string ans = "";
    do {
        int digit = x % b;
        ans = char('0' + digit) + ans;
        x /= b;
    } while (x > 0);
    return ans;
}

bool check(int x) {
    int cnt = 0;
    for (int b = 2; b <= 10; ++b) {
        string s = toBase(x, b);
        string t = s; reverse(t.begin(), t.end());
        if (s == t) cnt++;
        if (cnt >= 2) return true;
    }
    return false;
}

int main(){
    #ifndef LOCAL
    freopen("dualpal.in", "r", stdin);
    freopen("dualpal.out", "w", stdout);
    #endif
    
    int n, s;
    while (cin >> n >> s) {
        while (n > 0) {
            s++;
            if (check(s)) {
                cout << s << endl;
                n--;
            }
        }
    }
}