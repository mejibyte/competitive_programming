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
  
  int s = 1;
  while (!(k & s)){
    s <<= 1;
  }
  // s = smallest power of two in k
  
  int ans = 0;
  while (p > s){
    p >>= 1;
    ans++;
  }
  assert(p == s);
  cout << ans << endl;

  return 0;
}
