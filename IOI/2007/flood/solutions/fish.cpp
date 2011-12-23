#include <stdio.h>

#define MAX_N 100000

int n;
long long position[MAX_N];
long long food[MAX_N];

int ok( long long K )
{
  long long carry = 0;
  int i;

  for( i = 0; i < n - 1; ++i )
  {
    long long x = food[i] + carry;

    if( x < K )
    {
      carry = x - K - (position[i + 1] - position[i]);
    }
    else // if( x >= K )
    {
      carry = x - K - (position[i + 1] - position[i]);
      if(carry < 0) carry = 0;
    }
  }

  return (food[n - 1] + carry) >= K;
}

int main( void )
{
  int i;
  long long low = 0, high = 1;

  scanf( "%d", &n );

  for( i = 0; i < n; ++i )
  {
    scanf( "%lld%lld", &position[i], &food[i] );
    if( food[i] > high ) high = food[i];
  }

  while( low < high )
  {
    long long mid = (low + high + 1) / 2;
    if( ok( mid ) )
      low = mid;
    else
      high = mid - 1;
  }

  printf( "%lld\n", low );

  return 0;
}
