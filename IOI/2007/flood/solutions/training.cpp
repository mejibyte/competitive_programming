#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

#define MAXN 1000
#define MAXK 10

typedef pair<int,int> Pair;

struct Edge {
   int u, v; 
   int cost;
   int LCA; // lowest common ancestor of u and v
} E[MAXN*MAXK/2];

int n, m;
int costSum;
int traversalTime;
int discover[MAXN];
int finish[MAXN];
int depth[MAXN];
int degree[MAXN];
int color[MAXN];
Pair parent[MAXN];
vector<int> treeLinks[MAXN];

int DP[MAXN][1<<MAXK];

void load() {
   costSum = 0;
   scanf( "%d%d", &n, &m );
   for( int i = 0; i < m; ++i ) {
      scanf( "%d%d%d", &E[i].u, &E[i].v, &E[i].cost ); --E[i].u; --E[i].v;
      
      costSum += E[i].cost;
      if( E[i].cost == 0 ) {
         treeLinks[E[i].u].push_back( E[i].v );
         treeLinks[E[i].v].push_back( E[i].u );
      }
   }
}

void treeInit( int a ) {
   discover[a] = ++traversalTime;
   for( vector<int>::iterator it = treeLinks[a].begin(); it != treeLinks[a].end(); ++it ) {
      if( *it == parent[a].first ) continue;
      
      color[*it] = color[a] ^ 1;
      depth[*it] = depth[a] + 1;
      parent[*it] = Pair( a, 1<<degree[a]++ );

      treeInit( *it );
   }
   finish[a] = ++traversalTime;
}

void init() {
   memset( DP, 0, sizeof DP );
   
   traversalTime = 0;
   color[0] = 0;
   depth[0] = 0;
   parent[0] = Pair( -1, -1 );
   treeInit( 0 );
}

void calcLCA() {
   for( int i = 0; i < m; ++i ) {
      int u = E[i].u;
      int v = E[i].v;
      while( depth[u] > depth[v] ) u = parent[u].first;
      while( depth[v] > depth[u] ) v = parent[v].first;
      while( u != v ) { 
         u = parent[u].first;
         v = parent[v].first;
      }
      E[i].LCA = u;
   }
}

bool orderByLCAFinishTime( const Edge &A, const Edge &B ) {
   return finish[A.LCA] < finish[B.LCA];
}

void solve() {
   Pair U, V;
   for( int i = 0; i < m; ++i ) {
      if( E[i].cost != 0 && color[E[i].u] != color[E[i].v] ) continue;

      int L = E[i].LCA;
      int sum = E[i].cost;
      
      for( U = Pair(E[i].u, 0); U.first != L; U = parent[U.first] ) sum += DP[U.first][U.second];
      for( V = Pair(E[i].v, 0); V.first != L; V = parent[V.first] ) sum += DP[V.first][V.second];

      for( int mask = (1<<degree[L])-1; mask >= 0; --mask ) 
         if( !(mask & U.second || mask & V.second) ) 
            DP[L][mask] >?= sum + DP[L][mask | U.second | V.second];
   }
}

int main( void ) {
   load();
   init();
   calcLCA();
   sort( E, E+m, orderByLCAFinishTime );
   solve();
   printf( "%d\n", costSum - DP[0][0] );
   return 0;
}
