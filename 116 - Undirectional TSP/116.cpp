 #include <iostream>
 #include <vector>

using namespace std;

int main(){
  int rows, cols;
  while(cin >> rows >> cols){
    //g = matriz de entrada
    long long g[rows][cols];
    //dp[i][j] = minimo peso para llegar a la casilla (i,j)
    //empezando en cualquiera de la última columna
    long long dp[rows][cols];
    //p[i][j] = Fila en la que estuve antes de llegar a la casilla
    //(i,j), pero recorriendo la matriz de derecha a izquierda
    int p[rows][cols];
    for (int i=0; i<rows; ++i){
      for (int j=0; j<cols-1; ++j){
	cin >> g[i][j];
	dp[i][j] = LLONG_MAX;
	p[i][j] = -1;
      }
      cin >> g[i][cols-1];
      dp[i][cols-1] = g[i][cols-1];
      p[i][cols-1] = -1;
    }

    for (int j=cols-2; j>=0; --j){
      for (int i=0; i<rows; ++i){
	int previousRows[] = {(i+rows-1)%rows, i, (i+1)%rows };
	sort(previousRows, previousRows + 3);
	for (int k=0; k<3; ++k){
	  if (dp[previousRows[k]][j+1] < dp[i][j]){
	    dp[i][j] = dp[previousRows[k]][j+1];
	    p[i][j] = previousRows[k];
	  }	  
	}
	dp[i][j] += g[i][j];
      }
    }

    long long minWeight = LLONG_MAX, firstRow = -1;
    for (int i=0; i<rows; ++i){
      if (dp[i][0] < minWeight){
	firstRow = i;
	minWeight = dp[i][0];
      }
    }

    vector<int> path;
    int i = firstRow;
    int j = 0;
    while (j < cols-1){
      path.push_back(p[i][j]);
      i = p[i][j];
      ++j;
    }

    cout << firstRow + 1;
    for (int i=0; i<path.size(); ++i){
      cout << " " << path[i] + 1;
    }
    cout << endl;
    cout << minWeight << endl;
  }
  return 0;
}
