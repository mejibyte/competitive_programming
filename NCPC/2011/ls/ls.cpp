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

const int MAXN = 105;
bool dp[MAXN][MAXN];

bool match(const string &p, const string &s) {
    int P = p.size();
    int S = s.size();
    assert(p[P - 1] == '$' and s[S - 1] == '$');
    
    for (int j = 0; j < S; ++j) dp[P - 1][j] = false;
    dp[P - 1][S - 1] = true;
    
    // D(p);
    //  D(s);
    
    for (int i = P - 2; i >= 0; --i) {
        for (int j = S - 1; j >= 0; --j) {
            dp[i][j] = false;
            
            if (p[i] != '*') {
                dp[i][j] = (p[i] == s[j]) and dp[i + 1][j + 1];
            } else {
                dp[i][j] = dp[i + 1][j];
                if (j + 1 < S) dp[i][j] |= dp[i][j + 1];
            }
        }
    }
    // for (int i = 0; i < P; ++i) {
    //      for (int j = 0; j < S; ++j) {
    //          printf("%d ", dp[i][j]);
    //      }
    //      puts(" ");
    //  }
    return dp[0][0];
}

int main(){
    string p; cin >> p;
    p += '$';
    int n;
    cin >> n;
    while (n--) {
        string s; cin >> s;
        if (match(p, s + "$")) {
            cout << s << endl;
        }
    }
    
    return 0;
}
