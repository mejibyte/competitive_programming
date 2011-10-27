// Accepted - Little tricks to try to make it faster. Doesn't really work.
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
      int ret = c - '0';
      while( isdigit(c = read_char()) ) ret = (ret << 3) + (ret << 1) + c - '0';
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

int N, K;
char mat[MAXN+1][MAXN+1];

short r1[MAXK * 32], r2[MAXK * 32], c1[MAXK * 32], c2[MAXK * 32];

vector<int> regionsAt[MAXN+1][MAXN+1];

int totalRegions;

inline void fillRegion(int r, char letter) {
    for (int i = r1[r]; i <= r2[r]; ++i) {
        for (int j = c1[r]; j <= c2[r]; ++j) {
            mat[i][j] = letter;
        }
    }    
}

inline bool isEmpty(int r) {
    for (int i = r1[r]; i <= r2[r]; ++i) {
        for (int j = c1[r]; j <= c2[r]; ++j) {
            if (mat[i][j] != '.') return false;
        }
    }    
    return true;
}

bool backtrack(int cell, char face) {
    int cr = cell / N;
    int cc = cell % N;
    
    if (cr >= N or cc >= N) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                IO::write(mat[i][j]);
            }
            IO::write('\n');
        }
        return true;
    }
    
    if (mat[cr][cc] != '.') return backtrack(cell + 1, face);
    
    for (int k = 0, m = regionsAt[cr][cc].size(); k < m; ++k) {
        int r = regionsAt[cr][cc][k];
        if (!isEmpty(r)) continue;
        fillRegion(r, face);
        if (backtrack(cell + 1, face + 1)) return true;
        fillRegion(r, '.');
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
                regionsAt[i][j].clear();                
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
                            r1[totalRegions] = ii;
                            r2[totalRegions] = ii + height - 1;
                            c1[totalRegions] = jj;
                            c2[totalRegions] = jj + width - 1;
                            if (isEmpty(totalRegions)) {
                                regionsAt[ii][jj].push_back( totalRegions );
                                totalRegions++;
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