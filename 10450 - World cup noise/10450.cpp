#include <iostream>

using namespace std;

unsigned long long u[52], c[52];

int main(){
  u[1] = 1;
  c[1] = 1;
  for (int i=2; i<=51; ++i){
    u[i] = c[i-1];
    c[i] = c[i-1] + u[i-1];
  }
  int casos;
  cin >> casos;
  int n;
  for (int j=1; j<=casos; ++j){
    cin >> n;
    cout << "Scenario #" << j << ":" << endl;
    cout << u[n] + c[n] << endl << endl;
  }
  return 0;
}
