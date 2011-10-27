/*
  Problem: 10446 - The Marriage Interview :-)

  Author: Andrés Mejía-Posada

  Method: Top down dynamic programming with memoization.

  Accepted.
 */
#include <iostream>

using namespace std;

unsigned long long memo[62][62];

unsigned long long trib(int n, int back){
  if (n <= 1) return 1;
  if (memo[n][back] == -1){
    memo[n][back] = 1; //Esta invocación
    for(int i=1; i<=back; i++){
      memo[n][back] += trib(n-i, back);
    }
  }
  return memo[n][back];
}

int main(){
  int n, back, C = 1;
  memset(memo, -1, sizeof memo);
  while (cin >> n >> back &&  n <= 60){
    cout << "Case " << C++ << ": " << trib(n, back) << endl;
  }
  return 0;
}
