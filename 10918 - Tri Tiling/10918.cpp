/*
  Wrong Answer.
 */
#include <iostream>

using namespace std;


unsigned long long x[31], y[31], z[31];

int main(){
  x[0] = 1; y[0] = 0; z[0] = 2;
  x[1] = 0; y[1] = 2; z[1] = 0;
  for (int i=2; i<=30; ++i){
    x[i] = x[i-2] + y[i-1];
    y[i] = z[i-1];
    z[i] = 2*x[i-1] + y[i-1];
  }
  int n;
  while (cin >> n && n != -1){
    cout << x[n] << endl;
  }
  return 0;
}
