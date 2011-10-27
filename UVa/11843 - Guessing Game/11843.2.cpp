// Accepted
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

int memo[1005][25];

int f(int n, int s) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (s == 1) return n;
    
    if (memo[n][s] != -1) return memo[n][s];
    
    int best = 1<<28;
    for (int i = 0; i < n; ++i) {
        int option = 1 + max(   f(i, s-1),  f(n-i-1, s)  );
        best = min(best, option);
    }
    return memo[n][s] = best;
}

int main(){
    int C;
    cin >> C;
    memset(memo, -1, sizeof memo);
    while (C--) {
        int n, s;
        cin >> n >> s;
        assert(s > 0 and n > 0);
        int ans = f(n, s);
        printf("%d\n", ans);
    }
    return 0;
}