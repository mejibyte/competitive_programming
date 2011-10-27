#include <iostream>
using namespace std;
int main(){
  int n;
  while (cin >> n){
    long long s=0;
    if (n % 2 == 1) --n;
    while (n >= 0){
      s += (n/2)+1;
      n -= 2;
    }
    cout << s << endl;
  }
  return 0;
}
