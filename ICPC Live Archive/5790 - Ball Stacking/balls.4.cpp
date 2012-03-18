// Andrés Mejía

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

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

namespace IO {
   #define MAXBUFF (1<<18)
   char buffer[MAXBUFF], *p = buffer+MAXBUFF;
   
   inline char read_char() {
      if( p == buffer+MAXBUFF ) {
         fread( buffer, 1, MAXBUFF, stdin );
         p = buffer;
      }
      return *p++;
   }

   inline int read_int() {
      char c;
      while( !isdigit(c = read_char()) and c != '-' );
      int sign = 1;
      if (c == '-') sign = -1, c = read_char();
      int ret = c-'0';
      while( isdigit(c = read_char()) ) ret = ret * 10 + c-'0';
      return ret * sign;
   }
}

const int MAXN = 1001;

long long dp[MAXN][MAXN];

int main(){
    int n;
    while (n = IO::read_int()) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= i; ++j) {
                dp[i][j] = IO::read_int();
                if (i - 1 >= j) dp[i][j] += dp[i - 1][j];
            }
        }

        dp[n][n - 1] = 0;
        for (int j = n - 1; j >= 0; --j) {
            for (int i = j; i < n; ++i) {
                dp[i][j] += i + 1 < n ? dp[i + 1][j + 1] : dp[n - 1][j + 1];
                if (dp[i][j] < 0) dp[i][j] = 0;
                if (i - 1 >= j and dp[i - 1][j] > dp[i][j]) {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        printf("%lld\n", dp[n - 1][0]);
    }
    return 0;
}