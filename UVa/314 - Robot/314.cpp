/*
  Problem: 314 - Robot (UVa)
  Author: Andrés Mejía-Posada
  (http://blogaritmo.factorcomun.org)

*/

using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
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
#include <map>
#include <set>

#define D(x) cout << #x " is " << x << endl


struct state{
  short i, j, d, w;
  state(){} state(short i, short j, short d, short w) : i(i), j(j), d(d), w(w) {}
};

int di[] = {-1, +0, +1, +0}, dj[] = {+0, +1, +0, -1};

const int N = 51;

int g[N+1][N+1], t[N+2][N+2], n, m;
bool v[N+1][N+1][4];

void bfs(){
  short si, sj, fi, fj; string dir;
  cin >> si >> sj >> fi >> fj >> dir;
  short sd;
  switch (dir[0]){
  case 'n': sd = 0; break;
  case 'e': sd = 1; break;
  case 's': sd = 2; break;
  case 'w': sd = 3; break;
  }

  assert(t[si][sj]);
  if (t[fi][fj]){
    queue<state> q;
    memset(v, 0, sizeof v);
    q.push(state(si, sj, sd, 0));
    while (q.size()){

#define f q.front()
      short i = f.i, j = f.j, d = f.d, w = f.w;
#undef f

      q.pop();

      if (i < 0 || i > n || j < 0 || j > m || !t[i][j] || v[i][j][d]) continue;

      if (i == fi && j == fj){
	//printf("popped %d %d %d %d\n",i,j,d,w);
	cout << w << endl;
	return;
      }

      //printf("popped %d %d %d %d\n",i,j,d,w);
      v[i][j][d] = true;

      q.push(state(i, j, (d+1)%4, w+1));
      q.push(state(i, j, (d+3)%4, w+1));
      for (int k=1; k<=3; ++k){
	int ni = i+k*di[d], nj = j+k*dj[d];
	if (ni < 0 || ni > n || nj < 0 || nj > m || !t[ni][nj]) break;
	q.push(state(ni, nj, d, w+1));
      }

    }
  }
  cout << "-1\n";
}

int main(){
  while (cin >> n >> m && (n+m)){
    for (int i=0; i<n; ++i){
      for (int j=0; j<m; ++j){
	cin >> g[i][j];
      }
    }

    //Crear matriz t(ransformada)
    for (int i=0; i<=n; ++i){
      for (int j=0; j<=m; ++j){
	if (i == 0 || j == 0 || i == n || j == m) t[i][j] = 0;
	else t[i][j] = !g[i-1][j-1] && !g[i-1][j] && !g[i][j-1] && !g[i][j];
	//cout << t[i][j] << " ";
      }
      //cout << endl;
	
    }

    //Hacer BFS sobre t
    bfs();
  }
  return 0;
}
