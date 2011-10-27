#include <iostream>
#include <cassert>

#define D(x) cout << #x " = " << (x) << endl
using namespace std;

int main(){
  int k;
  cin >> k;

  int p = 1;
  while (p < k){
    p <<= 1;
  }


  cout << p << " ";
  
  int need = k, steps = 0, have = p;
  while (need > 0){
    if (have <= need){
      need -= have;
    }
    have /= 2;
    steps++;
  }

  cout << steps - 1 << endl;

  return 0;
}
