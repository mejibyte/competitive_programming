#include <iostream>

using namespace std;

int a[9][9];

//Construye un triangulito de tres pisos que tiene la cima en el bloque (i,j).
void f(int i, int j){
  int A = a[i][j], B = a[i+2][j], C = a[i+2][j+2];

  a[i+1][j]   = (A+B-C)/2; //X
  a[i+1][j+1] = (A-B+C)/2; //Y
  a[i+2][j+1] = (A-B-C)/2; //Z
}

int main(){
  int C;
  cin >> C;
  while (C--){
    for (int i=0; i<5; ++i){
      for (int j=0; j<=i; ++j){
        cin >> a[2*i][2*j];
      }
    }
    for (int i=0; i<4; ++i){
      for (int j=0; j<=i; ++j){
        f(2*i, 2*j);
      }
    }

    for (int i=0; i<9; ++i){
      for (int j=0; j<=i; ++j){
        cout << (j>0?" ":"") << a[i][j];
      }
      cout << endl;
    }
  }
  return 0;
}
