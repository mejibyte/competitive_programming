#include <iostream>

using namespace std;

int main(){
  int n;
  cin >> n;
  while (n){
    //procesar caso
    if (n <= 3 || n % 2 == 1){
      cout << "Impossible\n";
    }else{
      int mitad = n / 2;
      cout << mitad * 3 << endl; // # of edges
      for (int i=1; i<n; ++i){
	cout << i << " " << i+1 << endl; //borde
      }
      cout << n << " 1" << endl; // cerrar borde
      for (int i=1; i<= mitad; ++i){
	cout << i << " " << i+mitad << endl;
      }
    }
    cin >> n;
  }
  return 0;
}
