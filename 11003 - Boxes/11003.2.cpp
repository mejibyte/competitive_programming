/*
  Problem: 11003 - Boxes
  From the UVa Online Judge

  Author: Andrés Mejía-Posada
  http://blogaritmo.factorcomun.org

  Method: Dynamic programming
  Complexity: O(n^2)

  Accepted.
 */
#include <iostream>
#include <algorithm>

using namespace std;

const int maxBoxes = 1000;
const int maxLoad = 3000;
int dp[maxBoxes][maxLoad+1];
/*
  dp[i][j] =  maximum amount of boxes that can be stacked using boxes 0..i (included) such that I can still
  add j more weight units on top.
 */

int main(){
  int n;
  while (cin >> n && n){
    for (int i=0; i<n; ++i)
      for (int j=0; j<=maxLoad; ++j)
        dp[i][j] = 0;


    for (int i=0; i<n; ++i){
      int w, l;
      cin >> w >> l; //weight and load of box i-th
      for (int j=0; j<= maxLoad; ++j){
        if (j <= l) dp[i][j] = 1; //I can stack at least box i-th
        //But maybe I can create a bigger stack with the same strength not using box i-th
        if (i > 0) dp[i][j] = max(dp[i][j], dp[i-1][j]);

        if (j + w <= maxLoad && j <= l && i > 0){ //Now try to add box i-th on top of the previous boxes
          dp[i][j] = max(dp[i][j], dp[i-1][j+w]+1);
        }
      }
    }
    cout << dp[n-1][0] << endl;
  }
  return 0;
}
