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

const int MAXN = 1000001 * 2;

int border[MAXN];
char s[MAXN];

int main(){
    while (true) {
        gets(s);
        int n = strlen(s);
        if (n == 1 and s[0] == '.') break;
        assert(n > 0);
        if (n == 1) {
            printf("%d\n", n);
            continue;
        }
        for (int i = n; i < 2 * n; ++i) {
            s[i] = s[i - n];
        }
        s[2 * n] = '\0';
        assert(strlen(s) == 2 * n);
        
        border[0] = 0;
        for (int i = 1; i < 2 * n; ++i) {
            int k = border[i - 1];
            while (k > 0 and s[i] != s[k]) k = border[k - 1];
            if (s[i] == s[k]) k++;
            border[i] = k;
        }
        
        for (int i = n; i < 2 * n; ++i) {
            if (border[i] == n) {
                assert(n % (i - n + 1) == 0);
                printf("%d\n", n / (i - n + 1));
                break;
            }
        }
        
   }
    return 0;
}