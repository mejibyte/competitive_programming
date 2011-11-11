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

const int MAXN = 1e6 + 5;

int b[MAXN];
bool inside[MAXN];

int main(){
    string s;
    while (getline(cin, s)) {
        if (s == "") continue;
        
        int n = s.size();
        if (n < 3) {
            puts("Just a legend");
            continue;
        }
        
        memset(inside, 0, sizeof inside);
        b[0] = 0;
        for (int i = 1; i < n; ++i) {
            b[i] = b[i - 1];
            while (b[i] > 0 and s[i] != s[b[i]]) b[i] = b[b[i] - 1];
            if (s[i] == s[b[i]]) b[i]++;
        }
        
        //For(i, 0, n) printf("%d ", b[i]); puts("");
        for (int i = 1; i < n - 1; ++i) inside[b[i]] = true;
        
        int k = b[n - 1];
        while (k > 0) {
            if (inside[k]) { // found
                puts(s.substr(0, k).c_str());
                break;
            }
            k = b[k - 1];
        }
        if (k == 0) {
            puts("Just a legend");
        }
    }
    return 0;
}