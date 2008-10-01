/*
  Problem: H - 9-Puzzle
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

#define _for(i, a, b) for (int i=0, _n = b; i<_n; ++i)
#define _from(i, a, b) for (int i=a, _n = b; i>=_n; --i)

#define D(x) cout << #x " is " << x << endl

struct state { int s[3][3]; };

int encode(const state &s){ int r = 0; _for(i, 0, 3) _for(j, 0, 3) r = 10*r + s.s[i][j]; return r; }
void decode(int r, state &s) { _from(i, 2, 0) _from(j, 2, 0) s.s[i][j] = r%10, r/=10; }


map<int, int> prev;
map<int, string> choice;

void bfs(){
  queue<int> q;
  prev[123456789] = -1;
  q.push(123456789);
  while (q.size()){
    int x = q.front();
    q.pop();
    //D(x);

    state u; decode(x, u);
    //Horizontal
    for(int i=0, t; i<3; ++i){
      state v = u;
      t = v.s[i][0], v.s[i][0] = v.s[i][1], v.s[i][1] = v.s[i][2], v.s[i][2] = t;
      int y = encode(v);
      if (!prev.count(y)) prev[y] = x, choice[y] = string("H") + char(i+'1'), q.push(y);
    }

    //Vertical
    for(int i=0, t; i<3; ++i){
      state v = u;
      t = v.s[2][i], v.s[2][i] = v.s[1][i], v.s[1][i] = v.s[0][i], v.s[0][i] = t;
      int y = encode(v);
      if (!prev.count(y)) prev[y] = x, choice[y] = string("V") + char(i+'1'), q.push(y);
    }
  }
}

int main(){
  //assert(freopen("puzzle.in", "r", stdin) != NULL);
  bfs();
  for (int u, x; !(u = 0);){
    for (int i=0; i<9; ++i) cin >> x, u = 10*u + x;
    if (u == 0) break;
    if (!prev.count(u)) cout << "Not solvable" << endl;
    else{
      string s = "";
      for (int w = prev[u]; w != -1; w = prev[u = w]) s += choice[u];
      cout << s.size() / 2 << " " << s << endl;
    }
  }
  return 0;
}
