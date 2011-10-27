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
    string s, t;
    s.reserve(MAXN);
    t.reserve(MAXN);
    
    while (getline(cin, s)) {
        int n = s.size();
        t = s + "$" + s;
        reverse(t.begin(), t.begin() + n);
        
        p[0] = 0;
        for (int i = 1; i < 2 * n + 1; ++i) {
            p[i] = p[i - 1];
            while (p[i] > 0 and t[i] != t[p[i]]) p[i] = p[p[i] - 1];
            if (t[i] == t[p[i]]) p[i]++;
        }
        
        // puts("");
        // D(t);
        // for (int i = 0; i < 2 * n + 1; ++i) {
        //     printf("%d ", p[i]);
        // }
        // puts("");

        printf("%s", s.c_str());
        for (int i = 0; i <= n; ++i) {
            if (2 * i - n >= 0 and p[n + i] >= n - i) {
                //printf("i = %d works on the first case\n", i);
                for (int k = 2 * i - n - 1; k >= 0; --k) {
                    putchar(s[k]);
                }
                break;
            }
            
            if (i < n and 2 * i - n + 1 >= 0 and p[n + i + 1] >= n - i) {
                for (int k = 2 * i - n; k >= 0; --k) {
                    putchar(s[k]);
                }
                break;
            }
        }
        puts("");
    }
    return 0;
}