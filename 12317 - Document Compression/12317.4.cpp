// Equipo Poncho, Carriel y Ruana
// Accepted on UVa - This is the fastest implementation I could get.
using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
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
#include <stack>
#include <list>
#include <map>
#include <set>

template <class T> string toStr(const T &x)
{ stringstream s; s << x; return s.str(); }
template <class T> int toInt(const T &x)
{ stringstream s; s << x; int r; s >> r; return r; }

#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define D(x) cout << #x " = " << (x) << endl;

const double EPS = 1e-9;

int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

namespace IO {
#define MAXBUFF (1<<18)
   char buffer[MAXBUFF], *p = buffer+MAXBUFF;
   char buffer2[MAXBUFF], *p2 = buffer2;
   
   inline char read_char() {
      if( p == buffer+MAXBUFF ) {
         fread( buffer, 1, MAXBUFF, stdin );
         p = buffer;
      }
      return *p++;
   }

   inline int read_int() {
      char c;
      while( !isdigit(c = read_char()) );
      int ret = c-'0';
      while( isdigit(c = read_char()) ) ret = ret * 10 + c-'0';
      return ret;
   }

   void flush() {
      fwrite( buffer2, 1, p2-buffer2, stdout );
      p2 = buffer2;
   }

   inline void write( char c ) {
      if( p2 == buffer2+MAXBUFF ) {
         fwrite( buffer2, 1, MAXBUFF, stdout );
         p2 = buffer2;
      }
      *p2++ = c;
   }
}


const int MAXBASES = 105, oo = 1 << 28;
int bases[MAXBASES];

int B, D;
int dp[1 << 16];

void precompute(){    
    for (int mask = 0; mask < (1 << 16); ++mask) {
        dp[mask] = oo;
    }
    dp[0] = 0;

    for (int i = 0; i < B; ++i) {
        for (int mask = 0; mask < (1 << 16); ++mask) {
            if (dp[mask] >= oo) continue;
            int new_mask = mask | bases[i];
            int score = dp[mask] + 1;
            if (score < dp[new_mask]) dp[new_mask] = score;
        }
    }    
}

int main(){
    while (true) {
        B = IO::read_int();
        D = IO::read_int();
        if (B == 0 and D == 0) break;
        for (int i = 0; i < B; ++i) {
            bases[i] = 0;
            
            int k = IO::read_int();
            while (k--) {
                int x = IO::read_int(); x--;
                bases[i] |= (1 << x);
            }
        }
        precompute();
        for (int j = 0; j < D; ++j) {
            int doc = 0;
            int k = IO::read_int();
            while (k--) {
                int x = IO::read_int(); x--;
                doc |= (1 << x);
            }

            int ans = dp[doc];
            if (ans >= oo) ans = 0;
            printf("%d", ans);

            if (j + 1 < D) printf(" ");
        }
        puts("");
    }
    return 0;
}
