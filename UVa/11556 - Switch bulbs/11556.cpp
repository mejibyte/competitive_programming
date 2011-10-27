/*
  Problem: 11556 - Switch bulbs
  Author: Andrés Mejía-Posada
  (http://blogaritmo.factorcomun.org)

  Not judged yet
 */

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

int d[1<<15], suiche[40];

int main(){

  int T, caso = 1;
  scanf("%d", &T);

  while (T--){
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i=0, k, x; i<m; ++i){
      suiche[i] = 0;
      scanf("%d", &k);
      while (k--){
        scanf("%d", &x);
        suiche[i] |= (1 << x);
      }
    }

    for (int i=0; i<(1<<n); ++i) d[i] = INT_MAX;
    queue<int> q;
    d[0] = 0;
    q.push(0);

    while (q.size()){
      int u = q.front(); q.pop();
      for (int k=0; k<m; ++k){
        int v = u ^ suiche[k]; //Toggles lights
        if (d[u] + 1 < d[v]){
          d[v] = d[u] + 1;
          q.push(v);
        }
      }

    }

    printf("Case %d:\n", caso++);
    int queries;
    scanf("%d", &queries);
    while (queries--){
      int destiny = 0;
      char buf[16];
      scanf("%s", buf);
      for (int i=n-1; i>=0; --i){

        int bit = buf[i] - '0';
        destiny |= (bit << (n - i - 1));
      }
      printf("%d\n", d[destiny] < INT_MAX ? d[destiny] : -1);
    }
    printf("\n");
  }
  return 0;
}
