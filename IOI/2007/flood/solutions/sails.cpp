#include <algorithm>
#include <cstdio>
#include <cstring>

#define MAXN 100000
#define MAXH 100000
#define CEIL_LOG_MAXH 17

using namespace std;

struct jedro { int h, x; } a[MAXN];
bool operator < ( const jedro &A, const jedro &B ) { return A.h < B.h; }

int delta[MAXH+1];

namespace tournament {   
   int first[2<<CEIL_LOG_MAXH];
   int last[2<<CEIL_LOG_MAXH];

   int First( int a, int b, int i = 1, int lo = 0, int hi = MAXH+1 ) {
      if( lo >= b || hi <= a ) return -1;
      if( lo >= a && hi <= b ) return first[i];
      
      int mid = (lo+hi)/2;
      int L = First( a, b, 2*i, lo, mid );
      int R = First( a, b, 2*i+1, mid, hi );
      return L != -1 ? L : R;
   }

   int Last( int a, int b, int i = 1, int lo = 0, int hi = MAXH+1 ) {
      if( lo >= b || hi <= a ) return -1;
      if( lo >= a && hi <= b ) return last[i];
      
      int mid = (lo+hi)/2;
      int L = Last( a, b, 2*i, lo, mid );
      int R = Last( a, b, 2*i+1, mid, hi );
      return R != -1 ? R : L;
   }
   
   void Update( int x, int val, int i = 1, int lo = 0, int hi = MAXH+1 ) {
      if( lo > x || hi <= x ) return;
      if( lo+1 == hi ) {
         delta[x] += val;
         if( delta[x] ) first[i] = last[i] = x;
         else first[i] = last[i] = -1;
      } else {
         int mid = (lo+hi)/2;
         Update( x, val, 2*i, lo, mid );
         Update( x, val, 2*i+1, mid, hi );
         first[i] = first[2*i] != -1 ? first[2*i] : first[2*i+1];
         last[i] = last[2*i+1] != -1 ? last[2*i+1] : last[2*i];
      }
   }

   void Init() {
      memset( first, -1, sizeof first );
      memset( last, -1, sizeof last );
      Update( 0, MAXH+1 );
   }
};

int main( void ) {
   int n;
   scanf( "%d", &n );
   for( int i = 0; i < n; ++i ) scanf( "%d%d", &a[i].h, &a[i].x );
   sort( a, a+n );

   tournament::Init();
   for( int i = 0; i < n; ++i ) {
      int h0 = a[i].h - a[i].x;
      int h_up = tournament::First( h0, MAXH+1 );
      int h_down = tournament::Last( 0, h0+1 );
      if( h_up == -1 ) h_up = a[i].h;

      tournament::Update( a[i].h, 1 );
      tournament::Update( h_up, -1 );
      tournament::Update( h_down + h_up - h0, 1 );
      tournament::Update( h_down, -1 );
   }
   
   long long ret = 0, val = 0;
   for( int h = MAXH; h > 0; --h ) {
      val += delta[h];
      ret += val * (val-1)/2;
   }

   printf( "%lld\n", ret );

   return 0;
}
