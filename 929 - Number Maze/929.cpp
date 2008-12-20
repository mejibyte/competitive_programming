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
const int MAXN = 1000, MAXEDGE = 10;
int g[MAXN][MAXN], d[MAXN][MAXN];
int rows, cols;

struct state{
  int i, j, w;
};


queue<state> q[MAXEDGE];
int current_q;

void enqueue(int i, int j, int w){
  q[w % MAXEDGE].push((state){i, j, w});
}

bool dequeue(int &i, int &j, int &w){
  int started_at = current_q;
  while (q[current_q].empty()){
    current_q = (current_q + 1)%MAXEDGE;
    if (current_q == started_at) return false;
  }
  const state &s = q[current_q].front();
  i = s.i, j = s.j, w = s.w;
  q[current_q].pop();
  return true;
}

int dijkstra(){
  //clean queues
  for (int i=0; i<MAXEDGE; ++i){
    for (; q[i].size(); q[i].pop());
  }
  current_q = g[0][0];
  d[0][0] = g[0][0];
  enqueue(0, 0, g[0][0]);
  for (int i, j, w; dequeue(i, j, w); ){
    //printf("popped (%d, %d, %d)\n", i, j, w);
    if (w > d[i][j]) continue;
    if (i == rows-1 && j == cols-1) break;
    for (int di=-1; di<=1; ++di){
      for (int dj=-1; dj<=1; ++dj){
        if (di != 0 ^ dj != 0){
          int ni = i + di;
          int nj = j + dj;
          if (0 <= ni && ni < rows && 0 <= nj && nj < cols){
            int w_extra = g[ni][nj];
            if (w + w_extra < d[ni][nj]){
              d[ni][nj] = w + w_extra;
              enqueue(ni, nj, w + w_extra);
            }
          }
        }
      }
    }
  }
  return d[rows-1][cols-1];
}

int main(){
  int how_many;
  for (scanf("%d", &how_many); how_many--; ){
    scanf("%d %d", &rows, &cols);
    for (int i=0; i<rows; ++i){
      for (int j=0; j<cols; ++j){
        scanf("%d", &g[i][j]);

        //cleaning
        d[i][j] = INT_MAX;
      }
    }

    printf("%d\n", dijkstra());
  }
  return 0;
}
