#include <iostream>

using namespace std;

int g[226][226];
bool visited[226][226];

int r, c;
bool cycle;

//#define DEBUG

typedef pair<int, int> node;

int di[] = { 0, +1,  0, -1};
int dj[] = {+1,  0, -1,  0};

int shoot(const node &u, const node &dad, const node &start){
  
  int cuenta = 1;
  int i = u.first, j = u.second;

  visited[i][j] = true;
  //printf("Shooting (%d,%d)\n", i, j);  
  bool probable = false;
  for (int k=0; k<4; ++k){
    int ni = i + di[k];
    int nj = j + dj[k];

    //printf(" Objetivo: (%d,%d)\n", ni, nj);

    //printf("r y c son: %d, %d\n", r, c);

    if (0 <= ni && ni < 3*r &&
	0 <= nj && nj < 3*c &&
	g[ni][nj] != -1){
      
      if (!visited[ni][nj]){
	cuenta += shoot(node(ni, nj), u, start);
      }else if (node(ni, nj) == start && node(ni, nj) != dad){
	probable = true;
      }
    }
  }
  if (probable && cuenta == 1){
    cycle = true;
  }
  return cuenta;
}


int main(){
  int mazeNo = 1;
  while ( cin >> c >> r && r && c){

    for (int i=0; i<3*r; ++i) for (int j=0; j<3*c; ++j){ visited[i][j] =  g[i][j] = 0; }

    for (int i=0; i<r; ++i){
      for (int j=0; j<c; ++j){
	char d;
	cin >> d;
	if (d == '\\'){
	  g[3*i][3*j] = g[3*i+1][3*j+1] = g[3*i+2][3*j+2] = -1;
	}else if (d == '/'){
	  g[3*i][3*j+2] = g[3*i+1][3*j+1] = g[3*i+2][3*j] = -1;	  
	}
      }
    }


#ifdef DEBUG
    for (int i=0; i<3*r; ++i){
      for (int j=0; j<3*c; ++j){
	printf("%3d", g[i][j]);
      }
      cout << endl;
    }
    cout << endl;
    #endif

    int longest = -9999999;

    int count = 0;
    for (int i=0; i<3*r; ++i){
      for (int j=0; j<3*c; ++j){
	if (g[i][j] != -1 && !visited[i][j]){
	  
	  //printf("Shooting (%d,%d)\n", i, j);
	  
	  cycle = false;
	  int dist = shoot(node(i, j), node(-1,-1), node(i, j));
	  //cout << "Cycle of length " << dist << " found.\n";
	  if (cycle){
	    longest >?= dist;
	    ++count;
	  }
	}
      }
    }

    #ifdef DEBUG
    for (int i=0; i<3*r; ++i){
      for (int j=0; j<3*c; ++j){
	printf("%3d", g[i][j]);
      }
      cout << endl;
    }
    cout << endl;
    #endif

    printf("Maze #%d:\n", mazeNo++);
    if (count > 0){
      printf("%d Cycles; the longest has length %d.\n", count, longest/3);
    }else{
      printf("There are no cycles.\n");
    }
 
    cout << endl;
  }  
  return 0;
}
