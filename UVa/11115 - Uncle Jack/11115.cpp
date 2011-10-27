#include <iostream>
#include <cassert>

using namespace std;

int main(){
  int n, d;
  while (cin >> n >> d  && (n + d)){
    assert(n != 10 || d != 25);
    unsigned long long r = 1;
    for (int i=1; i<=d; ++i){
      r *= n;
    }
    cout << r << endl;
  }
}
