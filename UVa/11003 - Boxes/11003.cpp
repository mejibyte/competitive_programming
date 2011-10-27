/*
  Time limit exceeded.
 */
#include <iostream>
#include <algorithm>

using namespace std;

const int maxBoxes = 1000;
const int maxLoad = 3000;
int dp[maxBoxes][maxLoad+1];
/*
  dp[i][j] = Máxima cantidad de cajas que puedo apilar
  tal que la caja i-ésima esté encima y que pueda montar
  otros j kilos arriba.
*/
int w[maxBoxes], l[maxBoxes];

int main(){
  int n;
  while (cin >> n && n){

    for (int i=0; i<n; ++i)
      for (int j=0; j<=maxLoad; ++j)
        dp[i][j] = 0;


    int answer = -1;
    for (int i=0; i<n; ++i){
      cin >> w[i] >> l[i];
      for (int j=0; j<= l[i]; ++j){
        dp[i][j] = 1;
        if (j + w[i] <= maxLoad){
          for (int k=0; k<i; ++k){
            dp[i][j] = std::max(dp[i][j], dp[k][j+w[i]] + 1);
          }
        }
      }
      answer = std::max(answer, dp[i][0]);
    }
    cout << answer << endl;
  }
  return 0;
}
