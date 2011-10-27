#include <iostream>
#include <math.h>

using namespace std;

int main(){
  unsigned int t;
  cin >> t;
  while (t--){
    int n, m;
    cin >> n >> m;
    double x = ceil(n/2.0), y = ceil(m/2.0);
    if (n != m){
      cout << (unsigned long)(x*y)  << endl;
    }else{
      cout << (unsigned long)(x*y - (x*(x-1))/2.0)  << endl;
    }
  }
  return 0;
}
