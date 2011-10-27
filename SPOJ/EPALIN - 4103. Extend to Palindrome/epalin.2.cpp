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

const int MAXN = 100005 * 2;

int p[MAXN];

int main(){
    string s;
    s.reserve(MAXN);
    while (getline(cin, s)) {
        printf("%s", s.c_str());
        int n = s.size();
        s = s + "$" + s;
        reverse(s.begin(), s.begin() + n);

        p[0] = 0;
        for (int i = 1; i < 2 * n + 1; ++i) {
            p[i] = p[i - 1];
            while (p[i] > 0 and s[i] != s[p[i]]) p[i] = p[p[i] - 1];
            if (s[i] == s[p[i]]) p[i]++;
        }

        for (int i = p[2 * n]; i < n; ++i) {
            putchar(s[i]);
        }
        puts("");
    }
    return 0;
}