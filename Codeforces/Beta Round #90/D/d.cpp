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

const long long CO = 198159127;

const int MAXN = 1000010;

long long ha[MAXN], hb[MAXN], pw[MAXN];
int pr[2 * MAXN];

int main(){
    string a, b;
    while (getline(cin, a) && getline(cin, b)) {
        if (a.size() != b.size()) {
            printf("-1 -1\n");
            continue;
        }
        a = " " + a;
        b = " " + b;
        
        int n = a.size() - 1;
        
        ha[0] = hb[0] = 0;
        pw[0] = 1;
        for (int i = 1; i <= n; ++i) {
            ha[i] = ha[i-1] * CO + (long long)a[i];
            //printf("ha[%d] = %lld\n", i, ha[i]);
            hb[i] = hb[i-1] * CO + (long long)b[i];
            //printf("hb[%d] = %lld\n", i, hb[i]);
            pw[i] = pw[i-1] * CO;
        }
        
        string c(1 + 2*n + 1, ' ');
        for (int i = 1; i <= n; ++i) {
            c.at(i) = a.at(n-i+1);
        }
        c.at(n+1) = '$';
        for (int i = n + 2; i <= n + n + 1; ++i) {
            c.at(i) = b.at(i-n-1);
        }
        //cout << c << endl;
        
        int k = 0;
        pr[1] = 0;
        for (int i = 2; i <= n + n + 1; ++i) {
            while ( (k > 0) and (c[i] != c[k+1]) ) k = pr[k];
            if (c[i] == c[k + 1]) k++;
            pr[i] = k;
        }
        cout << c << endl;
        For(i, 1, c.size()) {
            printf("pr[i=%d] = %d\n", i, pr[i]);
        }
        
        int ri = -1, rj = -1;
        for (int i = 1; i <= n - 1; ++i) {
            if (a[i] != b[n-i+1]) break;
            int t = pr[n+1+n-i];
            if (t == 0) continue;
            int len = n-i-t;
            //printf("i is %d: lhs = %lld, rhs = %lld\n", i, ha[i+len] - ha[i] * pw[len],  hb[len] );
            if ((ha[i+len] - ha[i] * pw[len]) != hb[len]) continue;
            ri = i-1, rj = i + len;
        }
        printf("%d %d\n", ri, rj);
    }
    return 0;
}