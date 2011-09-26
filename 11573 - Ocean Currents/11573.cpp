/*
  Problem:
  Andrés Mejía-Posada (andmej@gmail.com)
*/
using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <numeric>
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
#include <list>
#include <map>
#include <set>

#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

char mat[1001][1001];
int d[1001][1001];
int rows, cols;
int si, sj, ei, ej;

int bfs(){
  for (int i=0; i<rows; ++i){
    for (int j=0; j<cols; ++j){
      d[i][j] = INT_MAX >> 1;
    }
  }
  d[si][sj] = 0;
  deque<pair<int, int> > q;
  q.push_front(make_pair(si, sj));
  while (q.size()){
    int i = q.front().first, j = q.front().second, w = d[i][j];
    q.pop_front();
    if (w > d[i][j]) continue;
    if (i == ei && j == ej) return w;
    static const int di[] = {-1, -1, +0, +1, +1, +1, +0, -1};
    static const int dj[] = {+0, +1, +1, +1, +0, -1, -1, -1};
    for (int k=0; k<8; ++k){
      int ni = i + di[k], nj = j + dj[k];
      if (0 <= ni && ni < rows && 0 <= nj && nj < cols){
        int w_extra = mat[i][j] - '0' != k;
        if (w + w_extra < d[ni][nj]){
          d[ni][nj] = w + w_extra;
          if (w_extra){
            q.push_back(make_pair(ni, nj));
          }else{
            q.push_front(make_pair(ni, nj));
          }
        }
      }
    }
  }
  return -1;
}

int main(){

  cin >> rows >> cols;
  for (int i=0; i<rows; ++i){
    for (int j=0; j<cols; ++j){
      cin >> mat[i][j];
    }
  }
  int n;
  cin >> n;
  while (n--){
    cin >> si >> sj >> ei >> ej;
    si--, sj--, ei--, ej--;
    cout << bfs() << endl;
  }
  return 0;
}
