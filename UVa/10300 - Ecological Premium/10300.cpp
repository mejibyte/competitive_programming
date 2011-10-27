#include <iostream>
using namespace std;

int main(){
  int casos;
  cin >> casos;
  while (casos--){
    unsigned long long r=0, a, c;
    unsigned i;
    cin >> i;
    while (i--){
      cin >> a >> c >> c;
      r += a*c;
    }
    cout << r << endl;    
  }
}
