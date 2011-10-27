/*
  Problem:
  572 - Oil deposits (UVa Online Judge)
  1959 - Oil deposits (TJU Online Judge)

  Author: Andrés Mejía-Posada (http://github.com/andmej/acm)
  Algorithm: Depth-first search
 */
#include <iostream>

using namespace std;

int di[] = {-1, -1, -1, +0, +1, +1, +1, +0};
int dj[] = {-1, +0, +1, +1, +1, +0, -1, -1};

int r, c;

char g[100][100];
bool v[100][100];

void dfs(const int &i, const int &j){
  if ( (0 <= i && i < r && 0 <= j && j < c) == false){
    return;
  }
  if (v[i][j] || g[i][j] == '*') return;

  v[i][j] = true;

  for (int k=0; k<8; ++k){
    dfs(i + di[k], j + dj[k]);
  }

}

int main(){
  while (cin >> r >> c && (r+c)){
    for (int i =0; i<r; ++i){
      for (int j=0; j<c; ++j){
        cin >> g[i][j];
        v[i][j] = false;
      }
    }

    int t = 0;
    for (int i =0; i<r; ++i){
      for (int j=0; j<c; ++j){
        if (!v[i][j] && g[i][j] == '@'){
          ++t;
          dfs(i, j);
        }
      }
    }

    cout << t << endl;
  }
  return 0;
}
