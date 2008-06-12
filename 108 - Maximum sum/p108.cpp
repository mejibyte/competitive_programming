#include <iostream>
#include <stdio.h>

using namespace std;

int m[203][203], dp[203][203];

int main(){
  int n;
  cin >> n;
  memset(m, 0, sizeof(m));
  memset(dp, 0, sizeof(dp));
  for (int i=1; i<=n; ++i)
    for (int j=1; j<=n; ++j)
      cin >> m[i][j];
  
  dp[1][1] = m[1][1];
  for (int i=1; i<=n; ++i)
    for (int j=1; j<=n; ++j)
      dp[i][j] = dp[i][j-1] + m[i][j] + dp[i-1][j] - dp[i-1][j-1];
 

//   cerr << "m es:\n";
//   for (int i=0; i<=n+1; ++i){
//       for (int j=0; j<=n+1; ++j)
// 	cerr << m[i][j] << " ";
//       cerr << endl;
//   }
//   cerr << "\ndp es:\n";
//   for (int i=0; i<=n+1; ++i){
//       for (int j=0; j<=n+1; ++j)
// 	cerr << dp[i][j] << " ";
//       cerr << endl;
//   }

  int max = m[0][0];
  for (int i=n; i>=1; --i)
    for (int j=n; j>=1; --j)
      for (int k=1; k<=i; ++k)
	for (int l=1; l<=j; ++l){
	  int a = dp[i][j] - dp[i-k][j] - dp[i][j-l] + dp[i-k][j-l];
	  if (a > max)
	    max = a;
	}
  cout << max << endl;
	  
  
}
