#include <algorithm>
#include <cmath>
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

int n, m;

typedef long long llint;
typedef pair<int,int> par;

const int dx[4] = { 1, 0, -1, 0 };
const int dy[4] = { 0, -1, 0, 1 }; 

struct tocka { // point
   int x, y;
   int komponenta;
   par link[4];
   int regija[4];
   tocka() {
      komponenta = -1;
      for( int i = 0; i < 4; ++i ) link[i] = par(-1,-1);
      for( int i = 0; i < 4; ++i ) regija[i] = -1;
   }
};
vector<tocka> tocke;

struct regija {
   int vrijeme_poplave; 
   llint povrsina;
   vector<int> niz;
   regija() { 
      povrsina = 0; 
      vrijeme_poplave = -1; 
   }
};

int smjer( int a, int b ) {
   if( tocke[a].y == tocke[b].y ) 
      if( tocke[a].x < tocke[b].x ) return 0; else return 2;
   else 
      if( tocke[a].y > tocke[b].y ) return 1; else return 3;
}

void bfs( int x, int k ) {
   queue<int> Q;
   tocke[x].komponenta = k;
   for( Q.push( x ); !Q.empty(); Q.pop() ) {
      x = Q.front();
      
      for( int i = 0; i < 4; ++i ) {
         int y = tocke[x].link[i].first;
         if( y != -1 && tocke[y].komponenta == -1 ) {
            tocke[y].komponenta = k;
            Q.push( y );
         }
      }
   }
}

void obidji( int i, int j, regija &R, int id ) { 
   R.niz.push_back( i );
   while( tocke[i].regija[j] == -1 ) {
      tocke[i].regija[j] = id;

      int k = tocke[i].link[j].first;
      R.povrsina += (tocke[i].x - tocke[k].x) * (llint) tocke[i].y;
      R.niz.push_back( k );

      i = k;
      for( j = (j+3)%4; tocke[i].link[j].first == -1; j = (j+1)%4 );
   }
   R.povrsina >?= -R.povrsina;
}

int main( void ) {
   scanf( "%d", &n );
   for( int i = 0; i < n; ++i ) {
      tocka t;
      scanf( "%d%d", &t.x, &t.y );
      tocke.push_back( t );
   }

   scanf( "%d", &m );
   for( int i = 0; i < m; ++i ) {
      int a, b;
      scanf( "%d%d", &a, &b ); --a; --b;
      
      tocke[a].link[smjer(a,b)] = par(b,i);
      tocke[b].link[smjer(b,a)] = par(a,i);
   }

   int broj_komponenti = 0;
   for( int i = 0; i < n; ++i ) 
      if( tocke[i].komponenta == -1 ) 
         bfs( i, broj_komponenti++ );   

   vector<int> vanjska_regija( broj_komponenti, -1 );
   vector<regija> regije;

   for( int i = 0; i < n; ++i ) 
      for( int j = 0; j < 4; ++j ) 
         if( tocke[i].link[j].first != -1 && tocke[i].regija[j] == -1 ) {
            int R = regije.size();
            regije.push_back( regija() );

            obidji( i, j, regije[R], R );

            int &vanjska = vanjska_regija[ tocke[i].komponenta ];
            if( vanjska == -1 ) vanjska = R;
            if( regije[R].povrsina > regije[vanjska].povrsina ) vanjska = R;
         }

   queue<int> Q; 
   for( int i = 0; i < broj_komponenti; ++i ) {
      if( vanjska_regija[i] == -1 ) continue;
      regije[ vanjska_regija[i] ].vrijeme_poplave = 0;
      Q.push( vanjska_regija[i] );
   }

   for( ; !Q.empty(); Q.pop() ) {
      int R = Q.front();
      
      for( int i = 1; i < regije[R].niz.size(); ++i ) {
         int a = regije[R].niz[i];
         int b = regije[R].niz[i-1];
         
         int S = tocke[a].regija[smjer(a,b)];
         
         if( regije[S].vrijeme_poplave == -1 ) {
            regije[S].vrijeme_poplave = regije[R].vrijeme_poplave + 1;
            Q.push( S );
         }
      }
   }

   vector<int> rjesenje;
   for( int a = 0; a < n; ++a ) 
      for( int i = 0; i < 4; ++i ) {
         int b = tocke[a].link[i].first;
         if( b == -1 || b < a ) continue;

         if( regije[tocke[a].regija[smjer(a,b)]].vrijeme_poplave == 
             regije[tocke[b].regija[smjer(b,a)]].vrijeme_poplave )
            rjesenje.push_back( tocke[a].link[i].second );
      }
         
   printf( "%d\n", rjesenje.size() );
   for( vector<int>::iterator it = rjesenje.begin(); it != rjesenje.end(); ++it ) 
      printf( "%d\n", *it + 1 );

   return 0;
}
