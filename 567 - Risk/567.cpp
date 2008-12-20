using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>

#define D(x) cout << #x " is " << x << endl

int g[21][21];

int main(){
  int C=1, len;
  while (scanf("%d", &len)==1){
    memset(g, 0x3F, sizeof g);

    for (int i=1; i<20; ++i){
      if (i > 1) scanf("%d", &len);
      for (int t=len, x; t--; ){
        scanf("%d", &x);
        g[i][x] = g[x][i] = 1;
      }
    }

    for (int k=1; k<=20; ++k)
      for (int i=1; i<=20; ++i)
        for (int j=1; j<=20; ++j)
          g[i][j] = min(g[i][j], g[i][k] + g[k][j]);

    printf("Test Set #%d\n", C++);
    int q;
    for (scanf("%d", &q); q--; ){
      int u, v;
      scanf("%d %d", &u, &v);
      printf("%2d to %2d: %d\n", u, v, g[u][v]);
    }
    puts("");
  }
  return 0;
}
