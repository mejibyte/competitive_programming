/*
  Problem: 574 - Sum it up (UVa Online Judge)
  Accepted

  Author: Andrés Mejía-Posada
 */
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector< vector<int> > matrix;

//for sorting the answer
bool compare(const vector<int> &a, const vector<int> &b) {
  int n = a.size(), m = b.size();
  for (int i=0; i<n && i<m; ++i){
    if (a[i] > b[i]) return true;
    if (b[i] > a[i]) return false;
  }
  return n < m;
}

void show(const vector<int> &v){
  printf("%d", v[0]);
  for (int i=1, n=v.size(); i<n; ++i){
    printf("+%d", v[i]);
  }
  printf("\n");
}

int main(){
  int t, n;
  while (scanf("%d %d", &t, &n) == 2 && n){
    int m[n];
    matrix dp[n][t+1];
    for (int i=0; i<n; ++i){
      scanf("%d", &m[i]);
    }

    dp[0][0].push_back(vector<int>());
    if (m[0] <= t){
      dp[0][m[0]].push_back(vector<int>(1, m[0]));
    }
    for (int i=1; i<n; ++i){
      for (int j=0; j<=t; ++j){
        dp[i][j] = dp[i-1][j];
        if (j - m[i] >= 0){
          for (int k=0; k<dp[i-1][j-m[i]].size(); ++k){
            dp[i][j].push_back(dp[i-1][j-m[i]][k]);
            dp[i][j].back().push_back(m[i]);
          }
        }
      }
    }

    /*for (int i=0; i<n; ++i){
      for (int j=0; j<=t; ++j){
        printf("(%d, %d) %d elementos: \n", i, j, dp[i][j].size());
        for (int k=0; k<dp[i][j].size(); ++k){
          for (int m=0; m<dp[i][j][k].size(); ++m){
            printf("%d ", dp[i][j][k][m]);
          }
          printf("\n");
        }
        printf("\n");
      }
      }*/
    matrix &answer = dp[n-1][t];
    sort(answer.begin(), answer.end(), compare);

    //printf("La respuesta tiene %d elementos\n", dp[n-1][t].size());
    printf("Sums of %d:\n", t);
    if (answer.size() == 0){
      printf("NONE\n");
    }else{
      show(answer[0]);
      for (int i=1; i<answer.size(); ++i){
        if (answer[i] != answer[i-1]) show(answer[i]);
      }
    }
  }
  return 0;
}
