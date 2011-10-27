#include <iostream>
using namespace std;

int main(){
  int h, m;
  cin >> h >> m;

  int mod = 24*60;
  h = h * 60 + m;
  h -= 45;
  h = (h + mod) % mod;
  
  cout << h / 60 << " " << h % 60 << endl; 
}
