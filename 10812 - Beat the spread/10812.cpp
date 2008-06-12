#include <iostream>

using namespace std;

int main(){
  int n;
  cin >> n;
  while (n--){
    unsigned long long s,d,x,y;
    cin >> s >> d;
    if (s < d || (s+d)%2 != 0 || (s-d)%2 != 0){
      cout << "impossible" << endl;
    }else{
      cout << (s+d)/2 << " " << (s-d)/2 << endl;
    }
  }
  return 0;
}
