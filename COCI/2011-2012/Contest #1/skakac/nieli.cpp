#include <cstdio>
#include <cstring>

int dx[] = {1,1,2,2,-1,-1,-2,-2};
int dy[] = {2,-2,1,-1,2,-2,1,-1};

int n, T;
int K[32][32];
bool vis[32][16];
int ok[2][1024][2], cnt[2];

int main()
{
	int i, j, k;
	int x, y;
	int pr, cr, t;
	int xn, yn;
	
	scanf( "%d %d", &n, &T );
	scanf( "%d %d", &x, &y );
	for ( i = 1; i <= n; i++ )
	{
		for ( j = 1; j <= n; j++ )
		{
			scanf( "%d", &K[i][j] );
		}
	}
	
	pr = 0;
	cr = 1;
	cnt[cr] = 1;
	ok[cr][1][0] = x;
	ok[cr][1][1] = y;
	xn = x; yn = y;
	for ( t = 1; t <= T; t++ )
	{
		cnt[pr] = 0;
		memset( vis, 0, sizeof( vis ) );
		for ( i = 1; i <= cnt[cr]; i++ )
		{
			x = ok[cr][i][0];
			y = ok[cr][i][1];
			for ( j = 0; j < 8; j++ )
			{
				if ( ( x+dx[j] < 1  ) || ( x + dx[j] > n ) || ( y + dy[j] < 1 ) || ( y + dy[j] > n ) ) continue;
				if ( ( vis[x+dx[j]][(y+dy[j])/2] == 0 ) && ( t%K[x+dx[j]][y+dy[j]] == 0 ) )
				{
					vis[x+dx[j]][(y+dy[j])/2] = 1;
					ok[pr][++cnt[pr]][0] = x+dx[j];
					ok[pr][cnt[pr]][1] = y+dy[j];
				}
			}
		}
		k = pr;
		pr = cr;
		cr = k;
	}
	
	k = 0;
	for ( i = 1; i <= n; i++ )
	{
		for ( j = 1; j <= n; j++ )
		{
			if ( (i+j+T)%2 != (xn+yn)%2 ) continue;
			k = k + vis[i][j/2];
		}
	}
	printf( "%d\n", k );
	for ( i = 1; i <= n; i++ )
	{
		for ( j = 1; j <= n; j++ )
		{
			if ( (i+j+T)%2 != (xn+yn)%2 ) continue;
			if ( vis[i][j/2] == 1 )
				printf( "%d %d\n", i, j );
		}
	}
	return 0;
}
