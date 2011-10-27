#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const int SIZE = 100000;

int f[SIZE+1];

int main(){
  f[0] = 0;
  int k;
  for (int i=1; i<=SIZE; ++i){
    f[i] = f[i-1] + ((k = (int)sqrt(i)) * k == i);
  }
  int a, b;
  while (cin >> a >> b && a+b){
    if (a > b) swap(a, b);
    cout << f[b] - f[a-1] << endl;
  }
  return 0;
}
