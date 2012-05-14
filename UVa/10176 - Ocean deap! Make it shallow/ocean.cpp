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

void solve(const string &s) {
    int power = 1, mod = 131071, ans = 0;
    for (int i = s.size() - 1; i >= 0; --i) {
        (ans += (s[i] - '0') * power) %= mod;
        (power <<= 1) %= mod;
    }
    puts(ans == 0 ? "YES" : "NO");
}

int main(){
    char c;
    string s = "";
    while (cin >> c)
        if (c == '#') solve(s), s = "";
        else s += c;
    return 0;
}