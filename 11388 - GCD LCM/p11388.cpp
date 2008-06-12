#include <iostream>

using namespace std;

int main(){
  int t;
  cin >> t;
  while(t--){
  unsigned int g,l;
  cin >> g >> l;
  if (g > l || l % g != 0)
    cout << "-1\n";
  else
    cout << g << " " << l << "\n";
  }
}
