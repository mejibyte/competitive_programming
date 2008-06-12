#include <iostream>

using namespace std;

int a[4];

int main(){
  int n;
  cin >> n;
  while (n--){
    cin >> a[0] >> a[1] >> a[2] >> a[3];
    sort(a, a+4);

    if (a[0] == a[1] && a[1] == a[2] && a[2] == a[3] && a[3] == a[0]){
      cout << "square" << endl;
      continue;
    }

    if (a[0] == a[1] && a[2] == a[3]){
      cout << "rectangle" << endl;
      continue;
    }
  
    if (a[0]+a[1]+a[2] >= a[3]){
      cout << "quadrangle" << endl;
      continue;
    }
    cout << "banana" << endl;
  }
  return 0;
}
