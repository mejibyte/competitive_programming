// Accepted, trying to make it run faster.
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
#include <bitset>
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
#define MAXBUFF (1<<20)
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
      char c = read_char();
      while( !isdigit(c) and c != '-' ) c = read_char();
      int sign = c == '-' ? -1 : +1;
      if (c == '-') c = read_char();
      int ret = c-'0';
      while( isdigit(c = read_char()) ) ret = ret * 10 + c-'0';
      return ret * sign;
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

struct point {
    int x, y;
    point(){} point(int x, int y) : x(x), y(y) {}
    bool operator < (const point &t) const {
        return x * t.y - y * t.x > 0;
    }
    bool operator == (const point &t) const {
        return x * t.y - y * t.x == 0;
    }
    bool operator <= (const point &t) const {
        return *this < t or *this == t;
    }
    bool operator != (const point &t) const {
        return !(*this == t);
    }    
};

typedef pair< point, point > interval;

// Returns true if interval 'a' is strictly included in interval 'b'
inline bool included(const interval &a, const interval &b) {
    return b.first < a.first and a.second < b.second;
}

const int MAXN = 1001;

interval intervals[MAXN];
int B;

inline void delete_redundant() {
    bitset<MAXN> deleted;
    for (int i = 0; i < B; ++i) {
        for (int j = 0; j < B; ++j) {
            // delete interval i if interval j is completely inside it
            if (included(intervals[j], intervals[i])) {
                deleted[i] = true;
                break;
            }
        }
    }
    int k = 0;
    for (int i = 0; i < B; ++i) {
        if (!deleted[i]) {
            intervals[k++] = intervals[i];
        }
    }
    B = k;
}

char buf[10];

int main(){
    while (B = IO::read_int()) {
        for (int i = 0; i < B; ++i) {
            point p1, p2;
            intervals[i].first.x = IO::read_int();
            intervals[i].first.y = IO::read_int();
            intervals[i].second.x = IO::read_int();
            intervals[i].second.y = IO::read_int();
            if (intervals[i].second < intervals[i].first) swap(intervals[i].first, intervals[i].second);
        }
        //printf("Before removing redundant B is %d\n", B);
        delete_redundant();
        sort(intervals, intervals + B);
        //printf("After removing redundant B is %d\n", B);
        
        //printf("Before removing duplicates B is %d\n", B);
        B = unique(intervals, intervals + B) - intervals;
        //printf("After removing duplicates B is %d\n", B);
        
        int ans = 0, i = 0;
        while (i < B) {
            ans++;
            point pick = intervals[i].second;
            while (i < B and intervals[i].first <= pick) i++;
        }
        sprintf(buf, "%d\n", ans);
        for (char * c = buf; *c; ++c) IO::write(*c);
    }
    IO::flush();
    return 0;
}