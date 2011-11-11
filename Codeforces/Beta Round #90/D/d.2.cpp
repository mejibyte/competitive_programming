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

const int MAXN = 1000005;

int p[2 * MAXN];
int z[2 * MAXN];

int main(){
    string a, b;
    while (getline(cin, a) and getline(cin, b)) {
        int n = a.size();
        if (n != b.size()) {
            puts("-1 -1");
            continue;
        }

        string s1 = a; reverse(s1.begin(), s1.end()); s1 += '\n' + b;
        string s2 = b + '\n' + a;

        // { s1 == a^r$b }
        // { s2 == b$a }

        // Find prefix function of a^r$b
        p[0] = 0;
        for (int i = 1; i < 2 * n + 1; ++i) {
            int k = p[i - 1];
            while (k > 0 and s1[i] != s1[k]) k = p[k - 1];
            if (s1[i] == s1[k]) k++;
            p[i] = k;
        }

        // Find z function of b$a
        z[0] = 0;
        for (int i = 1, l = 0, r = 0; i < 2 * n + 1; ++i) {
            z[i] = 0;
            if (i <= r) z[i] = min(z[i - l], r - i + 1);
            while (i + z[i] < 2 * n + 1 && s2[z[i]] == s2[i + z[i]]) ++z[i];
            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }

        int ans_i = -1, ans_j = -1;
        for (int i = 0; i < n; ++i) {
            if (a[i] != b[n - i - 1]) break;
            int len = p[2 * n - 1 - i]; // Length of s[j, n-1]^r
            if (len == 0) continue;
            if (z[n + 1 + i + 1] >= n - len - i - 1) {
                ans_i = i, ans_j = n - len;
            }
        }
        printf("%d %d\n", ans_i, ans_j);
    }
    return 0;
}