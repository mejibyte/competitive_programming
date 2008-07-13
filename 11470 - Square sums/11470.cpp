#include <iostream>

using namespace std;

const int SIZE = 10;

int g[SIZE][SIZE];

int main(){
  int n, C = 1;
  while(scanf("%d", &n) == 1 && n){
    for (int i=0; i<n; ++i){
      for (int j=0; j<n; ++j){
        scanf("%d", &g[i][j]);
      }
    }

    printf("Case %d:", C++);
    for (int i=0; i<(n/2); ++i){
      //printf("\ni es: %d\n", i);
      int s = 0;
      for (int j=i; j<=n-1-i; ++j){
        s += g[i][j];
        s += g[n-1-i][j];
      }
      for (int k=i+1; k<n-1-i; ++k){
        s += g[k][i] + g[k][n-1-i];
      }
      printf(" %d", s);
    }
    if (n & 1) printf(" %d", g[n/2][n/2]);
    puts("");
  }
  return 0;
}
