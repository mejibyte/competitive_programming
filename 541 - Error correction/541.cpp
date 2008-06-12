#include <iostream>

using namespace std;

int m[100][100];
//Contiene 0 si la fila o columna i es par, 1 si es impar
bool r[100], c[100];

int main(){
  int n;
  while (cin >> n && n){
    for (int i=0; i<n; ++i){
      for (int j=0; j<n; ++j){
	cin >> m[i][j];
      }
    }
    //rows
    for (int i=0; i<n; ++i){
      int res = 0;
      for (int j=0; j<n; ++j){
	res = (res + m[i][j]) % 2;
      }
      r[i] = res;
    }

    //columns
    for (int j=0; j<n; ++j){
      int res = 0;
      for (int i=0; i<n; ++i){
	res = (res + m[i][j]) % 2;
      }
      c[j] = res;
    }

    int oddRows=0, oddCols=0;

    int x, y;
    for (int i=0; i<n; ++i){
      oddRows += r[i];
      oddCols += c[i];
      if (r[i]) x = i;
      if (c[i]) y = i;
    }
    if (oddRows + oddCols == 0){
      cout << "OK";
    }else if (oddRows == 1 && oddCols == 1){
      cout << "Change bit ("<<x+1<<","<<y+1<<")";
    }else{
      cout << "Corrupt";
    }
    cout << endl;

  }
  return 0;
}

