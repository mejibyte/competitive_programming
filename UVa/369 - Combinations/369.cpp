#include <iostream>

using namespace std;

unsigned long long dp[101][101];


int main(){
  for (int i=0; i<=100; ++i){
    dp[i][0] = dp[i][i] = 1;
  }
  for (int i=1; i<=100; ++i)
    for (int j=1; j<=100; ++j)
      dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
  
  int n, m;
  cin >> n >> m;
  while (n + m){
    cout << n << " things taken " << m << " at a time is " << dp[n][m] << " exactly.\n";
    cin >> n >> m;
  }
    
  return 0;
}
