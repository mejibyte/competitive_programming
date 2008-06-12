#include <iostream>

using namespace std;

unsigned long long f[51];

int main(){
  f[0] = 0;
  f[1] = 1;
  f[2] = 2;
  for (int i=3; i<=50; ++i){
    f[i] = f[i-1] + f[i-2];
  }
  int n;
  while (cin >> n && n){
    cout << f[n] << endl;
  }
}
