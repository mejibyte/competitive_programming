/*
  Problem: A - Angry programmer
  Author: Andrés Mejía-Posada
  (http://blogaritmo.factorcomun.org)

  Accepted
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

namespace IO {
   #define MAXBUFF (1<<18)
    char buffer[MAXBUFF], *p = buffer+MAXBUFF;

    inline char read_char() {
        if( p == buffer+MAXBUFF ) {
            fread( buffer, 1, MAXBUFF, stdin );
            p = buffer;
        }
        return *p++;
    }

    inline int read_signed_int() {
        char c;
        while( !isdigit(c = read_char()) and c != '-' );
        int sign = 1;
        if (c == '-') sign = -1, c = read_char();
        int ret = c-'0';
        while( isdigit(c = read_char()) ) ret = ret * 10 + c-'0';
        return ret * sign;
    }

    inline int read_unsigned_int() {
        char c;
        while( !isdigit(c = read_char()) );
        int ret = c-'0';
        while( isdigit(c = read_char()) ) ret = ret * 10 + c-'0';
        return ret;
    }
}

const int MAXN = 2*51;

int cap[MAXN+1][MAXN+1], flow[MAXN+1][MAXN+1], prev[MAXN+1];

/*
  cap[i][j] = Capacidad de la arista (i, j).
  flow[i][j] = Flujo actual de i a j.
  prev[i] = Predecesor del nodo i en un camino de aumentación.
 */

int fordFulkerson(int n, int s, int t){
  int ans = 0;
  for (int i=0; i<n; ++i) fill(flow[i], flow[i]+n, 0);
  while (true){
    fill(prev, prev+n, -1);
    queue<int> q;
    q.push(s);
    while (q.size() && prev[t] == -1){
      int u = q.front();
      q.pop();
      for (int v = 0; v<n; ++v)
        if (v != s && prev[v] == -1 && cap[u][v] - flow[u][v] > 0 )
          prev[v] = u, q.push(v);
    }

    if (prev[t] == -1) break;

    int bottleneck = INT_MAX;
    for (int v = t, u = prev[v]; u != -1; v = u, u = prev[v]){
      bottleneck = min(bottleneck, cap[u][v] - flow[u][v]);
    }
    for (int v = t, u = prev[v]; u != -1; v = u, u = prev[v]){
      flow[u][v] += bottleneck;
      flow[v][u] = -flow[u][v];
    }
    ans += bottleneck;
  }
  return ans;
}


inline int in(int i){ return 2*i; }
inline int out(int i){ return 2*i+1; }

int main(){
  //assert(freopen("angry.in", "r", stdin) != NULL);
  ios::sync_with_stdio(false);
  int n, e;
  while (true) {
    n = IO::read_unsigned_int();
    e = IO::read_unsigned_int();
    if (n == 0 and e == 0) break;
    
    for (int i = 0; i < 2*n; ++i) {
        for (int j = 0; j < 2*n; ++j) {
            cap[i][j] = 0;
        }
    }

     //Las dos máquinas que no pueden ser destruídas.
    cap[in(0)][out(0)] = cap[in(n-1)][out(n-1)]= INT_MAX;
    

    //Costo de destrucción de máquinas.
    for (int k=2, i, w; k<n; ++k){
      i = IO::read_unsigned_int();
      w = IO::read_unsigned_int();
      --i;
      cap[in(i)][out(i)] = w;
    }

    //Costo de destrucción de cables.
    for (int k=0, i, j, w; k<e; ++k){
      i = IO::read_unsigned_int();
      j = IO::read_unsigned_int();
      w = IO::read_unsigned_int();
      --i, --j;
      cap[out(i)][in(j)] = cap[out(j)][in(i)] = w;
    }
    int ans = fordFulkerson(2*n, in(0), out(n-1));
    printf("%d\n", ans);
  }
  return 0;
}
