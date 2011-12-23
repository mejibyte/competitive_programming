#include <stdio.h>
#include <string.h>

static char vis[2001][2001];

int sol = 0;

void dfs( int r, int c )
{
   static const char *command[] = { "up", "down", "left", "right" };
   static const int dr[] = { -1, 1, 0, 0 };
   static const int dc[] = { 0, 0, -1, 1 };

   ++sol;

   for ( int dir=0; dir<4; ++dir ) {
      int nr = r+dr[dir], nc = c+dc[dir];
      if ( vis[1000+nr][1000+nc] ) continue;
      
      vis[1000+nr][1000+nc] = 1;

      char reply[10];
      puts( command[dir] ); fflush( stdout );
      scanf( "%s", reply );
      if ( strcmp( reply, "ok" ) == 0 ) {
         dfs( nr, nc );
         puts( command[dir^1] ); fflush( stdout );
         scanf( "%s", reply );
      }
   }
}

int main()
{
   vis[1000+0][1000+0] = 1;
   dfs(0, 0);
   printf( "%d\n", sol );
   return 0;
}
