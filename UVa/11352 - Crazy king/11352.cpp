#include <iostream>
#include <climits>
#include <queue>

using namespace std;

char g[101][101];

int deltaCol[] = {-2, -1,  1,  2, 2, 1, -1, -2};
int deltaFil[] = {-1, -2, -2, -1, 1, 2,  2,  1};

int rdeltaCol[] = { -1,  0,  1, 1, 1, 0, -1, -1};
int rdeltaFil[] = { -1, -1, -1, 0, 1, 1,  1,  0};

int inicialCol, inicialFil;

char color[101][101];
unsigned int d[101][101];

int m, n; //m filas, n columnas

const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;

void bfs(){
  memset(color, WHITE, sizeof(color));
  //memset(d, 2147483647, sizeof(d));

  for (int i=0; i<=100; ++i) for (int j=0; j<=100; ++j) d[i][j] = UINT_MAX;

  color[inicialFil][inicialCol] = GRAY;
  d[inicialFil][inicialCol] = 0;

  queue< pair<int,int> > q;
  q.push(make_pair(inicialFil, inicialCol));

  //printf("Empezando en: (%d,%d)\n", inicialFil, inicialCol);

  while (!q.empty()){
    int fil = q.front().first, col = q.front().second;

    //printf("Saque el nodo (%d,%d) de la cola.\n", fil, col);

    if (g[fil][col] == 'B'){
      cout << "Minimal possible length of a trip is ";
      cout << d[fil][col] << endl;
      return;
    }

    for (int k=0; k<8; ++k){
      int tempFil, tempCol;
      tempFil = fil + rdeltaFil[k];
      tempCol = col + rdeltaCol[k];
      //if (tempFil >= 0 && tempFil < m && tempCol >= 0 && tempCol < n){
      if ( (tempFil >= 0) && (tempFil < m) && (tempCol >= 0) && (tempCol < n)){
	char c = g[tempFil][tempCol];
	
	//printf("Considerando para marcado el nodo(%d,%d) que contiene %c\n", tempFil, tempCol, c);
	
	if (c != 'Z' && c != 'X'){

	  //printf("Nodo visitable (%d,%d), revisando que sea blanco.\n", tempFil, tempCol);

	  if (color[tempFil][tempCol] == WHITE){
	    color[tempFil][tempCol] = GRAY;
	    
	    //printf("Marcando gris el nodo (%d,%d)\n", tempFil, tempCol);

	    d[tempFil][tempCol] = d[fil][col] + 1;
	    q.push(make_pair(tempFil, tempCol));
	  }
	}
      }
    }
    q.pop();
    color[fil][col] = BLACK;
  }
  printf("King Peter, you can't go now!\n");
}
  

int main(){
  int casos;
  cin >> casos;
  while (casos--){
    cin >> m >> n;
    for (int i=0; i<m; ++i){
      for (int j=0; j<n; ++j){
	char c;
	cin >> c;
	g[i][j] = c;	
	if (c == 'A'){
	  inicialFil = i;
	  inicialCol = j;
	}
      }
    }



    for (int i=0; i<m; ++i){
      for (int j=0; j<n; ++j){
	if (g[i][j] == 'Z'){
	  for (int k=0; k<8; ++k){
	    int tempFil, tempCol;
	    tempFil = i + deltaFil[k];
	    tempCol = j + deltaCol[k];
	    if (tempFil >= 0 && tempFil <= m && tempCol >=0 && tempCol < n){
	      char c = g[tempFil][tempCol];
	      if (c != 'B' && c != 'A' && c != 'Z') g[tempFil][tempCol] = 'X';
	    }
	  }
	}
      }
    }      

    //En este momento, g[i][j] contiene una X si es una casilla atacable

    bfs();
    

    /*for (int i=0; i<m; ++i){
      for (int j=0; j<n; ++j){
	cerr <<	g[i][j];	
      }
      cerr << endl;
    }
    cerr << endl;
    */


  }
}
