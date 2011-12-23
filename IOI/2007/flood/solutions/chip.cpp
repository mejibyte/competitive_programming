#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct coords {
  char x, y; string s;
  coords( int xx, int yy ) { x=xx; y=yy; }
  int id() { return 32*(int)x+(int)y; }
  friend bool operator  < ( coords a, coords b ) { return a.id()  < b.id(); }
  friend bool operator == ( coords a, coords b ) { return !(a<b) && !(b<a); }
};

struct stanje {
  char i, g, d, y1, y2;
  stanje() {}
  stanje( char ii, char gg, char dd, char yy1, char yy2 ) { i=ii; g=gg; d=dd; y1=yy1; y2=yy2; }
  int id() { return 32*(32*(32*(32*(int)i+(int)g)+(int)d)+(int)y1)+(int)y2; }
  friend bool operator < ( stanje a, stanje b ) { return a.id() < b.id(); }
};

vector<coords> tocke, sorted;
vector<char> minx(32,32), maxx(32,0), miny(32,32), maxy(32,0);
int n, A;

map< stanje, short > memo;
map< stanje, pair<char, stanje> > how;

short rec( stanje p ) {
  if( p.i == n ) return 0;
  if( memo.count( p ) ) return memo[p];

  short ret = 1500;
  pair<char, stanje> h;

  coords t = sorted[p.i];
  if( minx[t.y] == t.x && t.y > p.d && t.y < p.g ) {
    stanje q( p.i+1, p.g, p.d, p.y1, p.y2 );
    short r = rec( q ) + t.x;
    if( r < ret ) { ret = r; h.first = 'L'; h.second = q; }
  }
  if( miny[t.x] == t.y && t.y < p.y1 ) {
    stanje q( p.i+1, p.g, max(p.d, t.y), p.y1, p.y2 );
    short r = rec( q ) + t.y;
    if( r < ret ) { ret = r; h.first = 'D'; h.second = q; }
  }
  if( maxy[t.x] == t.y && t.y > p.y2 ) {
    stanje q( p.i+1, min(p.g, t.y), p.d, p.y1, p.y2 );
    short r = rec( q ) + A-t.y;
    if( r < ret ) { ret = r; h.first = 'U'; h.second = q; }
  }
  if( maxx[t.y] == t.x ) {
    stanje q( p.i+1, p.g, p.d, min(p.y1, t.y), max(p.y2, t.y) );
    short r = rec( q ) + A-t.x;
    if( r < ret ) { ret = r; h.first = 'R'; h.second = q; }
  }

  how[p] = h;
  return memo[p] = ret;
}

void reconstruct( stanje p ) {
  if( p.i == n ) return;
  string s;
  if( how[p].first == 'L' ) s = "left";
  if( how[p].first == 'R' ) s = "right";
  if( how[p].first == 'U' ) s = "up";
  if( how[p].first == 'D' ) s = "down";
  find( tocke.begin(), tocke.end(), sorted[p.i] )->s = s;
  reconstruct( how[p].second );
}

void output( short ret ) {
  reconstruct( stanje( 0, A, 0, A, 0 ) );
  cout << ret << endl;
  for( int i = 0; i < n; ++i ) cout << tocke[i].s << endl;
}

int main( void ) {
  cin >> A >> n;
  for( int i = 0; i < n; ++i ) {
    int x, y; cin >> x >> y;
    tocke.push_back( coords( x, y ) );
    minx[tocke[i].y] <?= tocke[i].x; maxx[tocke[i].y] >?= tocke[i].x;
    miny[tocke[i].x] <?= tocke[i].y; maxy[tocke[i].x] >?= tocke[i].y;
  }

  sorted = tocke;
  sort( sorted.begin(), sorted.end() );

  output( rec( stanje( 0, A, 0, A, 0 ) ) );

  return 0;
}
