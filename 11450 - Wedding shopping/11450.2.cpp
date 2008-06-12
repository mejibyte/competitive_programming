/*
  Accepted
 */
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
  int N;
  scanf("%d", &N); //cin >> N;
  while (N--){
    int T, C;
    scanf("%d %d", &T, &C); //cin >> T >> C;
    vector< vector<int> > w;
    for (int i=0; i<C; ++i){
      int K;
      scanf("%d", &K); //cin >> K;
      vector<int> row(K);
      for (int j=0; j<K; ++j){
	scanf("%d", &row[j]);//cin >> row[j];
      }
      w.push_back(row);
    }

    bool dp[T+1][C];
    memset(dp, 0, sizeof dp);

    for (int j=0; j<w[0].size(); ++j){
      dp[w[0][j]][0] = true; //Primer nivel
    }
    
    for (int i=1; i<C; ++i){
      for (int t=0; t<=T; ++t){
	for (int j=0; j<w[i].size(); ++j){
	  if (t - w[i][j] >= 0){
	    if (dp[t-w[i][j]][i-1]){
	      dp[t][i] = true;
	      break;
	    }
	  }
	}
      }
    }
    
    bool solved = false;
    for (int t=T; t>=0; --t){
      if (dp[t][C-1]){
	printf("%d\n", t);//cout << t << endl;
	solved = true;
	break;
      }
    }
    
    if (!solved){
      printf("no solution\n");//cout << "no solution" << endl;
    }
  }
  return 0;
}
