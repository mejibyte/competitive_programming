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

const int MAXN = 1000005;

int f[MAXN];

void precomputePrefixFunction(char s[], int n) {
    f[0] = -1;
    for (int i = 1; i < n; ++i) {
        f[i] = f[i-1];
        while (f[i] > -1 and s[f[i]+1] != s[i]) {
            f[i] = f[f[i]];
        }
        if (s[f[i]+1] == s[i]) {
            f[i]++;
        }
    }
}

char s[MAXN];

int main(){
    // s = " abcabcabcabc";
    // precomputePrefixFunction(s);
    // for (int i = 1; i < s.length(); ++i) {
    //     printf("%d ", f[i]);
    // }
    // puts("");

    while (true) {
        gets(s);
        int n = strlen(s);
        if (n == 1 and s[0] == '.') break;
        assert(n > 0);
        if (n <= 1) {
            printf("%d\n", n);
            continue;
        }
        precomputePrefixFunction(s, n);

        //printf("s = %s\n", s); for (int i = 0; i < s; ++i) { printf("%d ", f[i]); } puts("");
        int periodSize = n;

        for (int j = n - 1; j - 1 >= 0 and f[j-1] <= f[j] and f[j] > 0; j--) {
            int k = n - j;
            if ((n % k == 0) and (j - 1) >= k) {
                periodSize = k;
            }
        }
        //printf("periodSize is %d\n", periodSize);
        assert((n % periodSize) == 0);
        printf("%d\n", n / periodSize);
    }
    return 0;
}