/*
  Accepted

  Andrés Mejía Posada
  http://blogaritmo.factorcomun.org
 */
#include <iostream>
#include <queue>

using namespace std;

int di[] = { +0, +0, +1, -1};
int dj[] = { +1, -1, +0, +0};

int main(){
  int n;
  cin >> n;
  while (n--){
    string name;
    int r, c;
    cin >> name >> r >> c;
    //dp[i][j] = length of longest valid path ending at position (i,j)
    int g[r][c], dp[r][c];
    queue<pair<int, int> > q;
    for (int i=0; i<r; ++i){
      for (int j=0; j<c; ++j){
        cin >> g[i][j];
        dp[i][j] = 1;
        q.push(make_pair(i, j));
      }
    }

    while (q.size()){
      int i = q.front().first;
      int j = q.front().second;
      q.pop();

      for (int k=0; k<4; ++k){
        int ni = i + di[k];
        int nj = j + dj[k];
        if (0 <= ni && ni < r &&
            0 <= nj && nj < c &&
            g[ni][nj] < g[i][j] &&
            dp[ni][nj] < dp[i][j] + 1){
          dp[ni][nj] = dp[i][j] + 1;
          q.push(make_pair(ni, nj));
        }
      }
    }
    int best = -1;
    for (int i=0; i<r; ++i){
      best = max(best, *max_element(dp[i], dp[i]+c));
    }

    cout << name << ": " << best << endl;
  }
  return 0;
}
