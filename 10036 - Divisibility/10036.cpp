/*
  Accepted
 */
#include <iostream>

using namespace std;

const int MAXN = 10000, MAXK = 100;

bool dp[MAXN][MAXK];

int main(){
  int cases;
  cin >> cases;
  while (cases--){
    int n, k;
    cin >> n >> k;
    if ( (0 <= n && n <= MAXN && 0 <= k && k <= MAXK) == false ) while (1);
    int a[n];
    for (int i=0; i<n; ++i){
      for (int j=0; j<k; ++j){
        dp[i][j] = false;
      }
      cin >> a[i];
    }

    dp[0][abs(a[0])%k] = true;
    for (int i=0; i<n-1; ++i){
      for (int j=0; j<k; ++j){
        if (dp[i][j]){
          int t = j + a[i+1];
          while (t < 0) t += k;
          dp[i+1][t%k] = true;

          t = j - a[i+1];
          while (t < 0) t += k;
          dp[i+1][t%k] = true;
        }
      }
    }

    cout << (dp[n-1][0]?"D":"Not d") << "ivisible" << endl;
  }
  return 0;
}
