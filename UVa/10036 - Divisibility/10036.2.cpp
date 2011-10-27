/*
  Accepted
 */
#include <iostream>

using namespace std;

const int MAXN = 10000, MAXK = 100;

bool dp[MAXN][MAXK];
int a[MAXN];

int main(){
  int cases;
  cin >> cases;
  while (cases--){
    int n, k;
    cin >> n >> k;
    if ( (0 <= n && n <= MAXN && 0 <= k && k <= MAXK) == false ) while (1);
    for (int i=0; i<n; ++i){
      cin >> a[i];
    }

    for (int j=0; j<k; ++j){
      dp[0][j] = false;
    }

    int t = a[0];
    while (t < 0) t += k;
    dp[0][t%k] = true;
    for (int i=1; i<n; ++i){
      for (int j=0; j<k; ++j){
        dp[i][j] = false;
        t = j + a[i];
        while (t < 0) t += k;
        dp[i][j] |= dp[i-1][t%k];

        t = j - a[i];
        while (t < 0) t += k;
        dp[i][j] |= dp[i-1][t%k];
      }
      }

    cout << (dp[n-1][0]?"D":"Not d") << "ivisible" << endl;
  }
  return 0;
}
