/*

  Problem: 11110 - Equidivisions

  Andrés Mejía-Posada
  
 */
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

const int MAXN = 110;

int  n;
int  g[MAXN+1][MAXN+1];
bool v[MAXN+1][MAXN+1];

//Retorna el número de casillas visitadas empezando en la casilla (i,j) si es de color c.
int dfs(int i, int j, int c){
  if ( (0 <= i && i < n && 0 <= j && j < n &&
	!v[i][j] && c == g[i][j]) == false )
    return 0;
  int ans = 1;
  v[i][j] = true;
  for (int di=-1; di<=1; ++di){
    for (int dj=-1; dj<=1; ++dj){
      if ((di == 0 || dj == 0) && (di != 0 || dj != 0) ){
	ans += dfs(i+di, j+dj, c);
      }
    }
  }
  return ans;
}

bool todo_bien(){
  for (int color=0; color<n; ++color){
    for (int i=0; i<n; ++i){
      for (int j=0; j<n; ++j){
	if (g[i][j] == color && !v[i][j]){
	  if (dfs(i, j, color) != n) return false;
	}
      }
    }
  }
  return true;
}

int main(){
  while (cin >> n && n){
    string line;
    getline(cin, line);
    memset(g, 0, sizeof g);
    memset(v, 0, sizeof v);
    for (int i=1; i<n; ++i){
      //Leer la partición de color i.
      //La partición que no está indicada es de color 0.

      getline(cin, line);
      stringstream sin(line);
      int r, c;
      while (sin >> r >> c) g[--r][--c] = i;
    }

    cout << (todo_bien() ? "good" : "wrong") << endl;
  }
  return 0;
}
