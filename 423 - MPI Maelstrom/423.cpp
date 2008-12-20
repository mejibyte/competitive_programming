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

const int oo = INT_MAX >> 2;
int g[100][100];

int main(){
  int n;
  scanf("%d", &n);

  for (int i=1; i<n; ++i){
    for (int j=0, x; j<i; ++j){
      char buf[32];
      scanf("%30s", buf);
      if (!strcmp(buf, "x")){
        x = oo;
      }else{
        x = atoi(buf);
      }
      g[i][j] = g[j][i] = x;
    }
    g[i][i] = 0;
  }

  for (int k=0; k<n; ++k){
    for (int i=0; i<n; ++i){
      for (int j=0; j<n; ++j){
        g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
      }
    }
  }

  int ans = -1;
  for (int j=0; j<n; ++j){
    ans = max(ans, g[0][j]);
  }

  printf("%d\n", ans);
  return 0;
}
