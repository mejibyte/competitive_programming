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

namespace IO {
#define MAXBUFF (1<<18)
   char inBuffer[MAXBUFF], *pIn = inBuffer+MAXBUFF;
   char outBuffer[MAXBUFF], *pOut = outBuffer;
   
   inline char read_char() {
      if( pIn == inBuffer+MAXBUFF ) {
         fread( inBuffer, 1, MAXBUFF, stdin );
         pIn = inBuffer;
      }
      return *pIn++;
   }

   inline int read_int() {
      char c;
      while( !isdigit(c = read_char()) );
      int ret = c-'0';
      while( isdigit(c = read_char()) ) ret = ret * 10 + c-'0';
      return ret;
   }

   void flush() {
      fwrite( outBuffer, 1, pOut-outBuffer, stdout );
      pOut = outBuffer;
   }

   inline void write( char c ) {
      if( pOut == outBuffer+MAXBUFF ) {
         fwrite( outBuffer, 1, MAXBUFF, stdout );
         pOut = outBuffer;
      }
      *pOut++ = c;
   }
}

const int MAXN = 20;
const int MAXK = 26;

struct region {
    short r1, r2, c1, c2;
    region() {}
    region(short r1, short r2, short c1, short c2) : r1(r1), r2(r2), c1(c1), c2(c2) {}
};

int N, K;
char mat[MAXN+1][MAXN+1];
region regions[MAXK * 32];
int totalRegions;

inline void fillRegion(const region &r, char letter) {
    for (int i = r.r1; i <= r.r2; ++i) {
        for (int j = r.c1; j <= r.c2; ++j) {
            mat[i][j] = letter;
        }
    }    
}

inline bool isEmpty(const region &r) {
    for (int i = r.r1; i <= r.r2; ++i) {
        for (int j = r.c1; j <= r.c2; ++j) {
            if (mat[i][j] != '.') return false;
        }
    }    
    return true;
}

bool backtrack(int cell, char face) {
    int r = cell / N;
    int c = cell % N;
    
    if (r >= N or c >= N) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                IO::write(mat[i][j]);
            }
            IO::write('\n');
        }
        return true;
    }
    
    if (mat[r][c] != '.') return backtrack(cell + 1, face);
    
    for (int k = 0; k < totalRegions; ++k) {
        const region &rg = regions[k];
        if (r != rg.r1 or c != rg.c1) continue;
        if (!isEmpty(rg)) continue;
        fillRegion(rg, face);
        if (backtrack(cell + 1, face + 1)) return true;
        fillRegion(rg, '.');
    }
    return false;
}

int main(){
    while (true) {
        N = IO::read_int();
        K = IO::read_int();
        if (N == 0 and K == 0) break;
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                char c = IO::read_char(); while (isspace(c)) c = IO::read_char();
                mat[i][j] = c;
            }
        }

        totalRegions = 0;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (mat[i][j] == '.') continue;
                int size = mat[i][j] - '0';
                mat[i][j] = '.';                
                for (int width = 1; width <= size; ++width) {
                    if (size % width != 0) continue;
                    int height = size / width;
                    for (int ii = max(0, i - height + 1); ii + height - 1 < N and ii <= i; ++ii) {
                        for (int jj = max(0, j - width + 1); jj + width - 1 < N and jj <= j; ++jj) {
                            region r(ii, ii + height - 1, jj, jj + width - 1);
                            if (isEmpty(r)) {
                                regions[totalRegions++] = r;
                            }
                        }
                    }
                }
                mat[i][j] = '0' + size;
            }
        }
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                mat[i][j] = '.';
            }
        }
        backtrack(0, 'A');
    }
    IO::flush();
    return 0;
}