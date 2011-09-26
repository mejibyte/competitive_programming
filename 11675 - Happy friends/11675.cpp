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
#include <list>
#include <map>
#include <set>

template <class T> string toStr(const T &x){ stringstream s; s << x; return s.str(); }
template <class T> int toInt(const T &x){ stringstream s; s << x; int r; s >> r; return r; }

#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define D(x) cout << #x " = " << (x) << endl

#define assign(x, y) memcpy(x, y, sizeof(y))

const int MOD = 1000000007;
const int MAXN = 35;

vector<int> g[MAXN];
int day[MAXN];

int odd[MAXN][MAXN], even[MAXN][MAXN], T[MAXN][MAXN], C[MAXN][MAXN], ans[1][MAXN];

void mul(int A[MAXN][MAXN], int B[MAXN][MAXN], int C[MAXN][MAXN], int p, int q, int r){
  for (int i=0; i<p; ++i){
    for (int j=0; j<r; ++j){
      C[i][j] = 0;
      for (int k=0; k<q; ++k){
        C[i][j] += A[i][k] * B[k][j];
        C[i][j] %= MOD;
      }
    }
  }
}



void exp(int A[MAXN][MAXN], int C[MAXN][MAXN], int n, int e){
  int TT[MAXN][MAXN];
  if (e == 0){
    for (int i=0; i<n; ++i){
      for (int j=0; j<n; ++j){
        C[i][j] = 0;
      }
      C[i][i] = 1;
    }
    return;
  }

  if (e == 1){
    assign(C, A);
    return;
  }

  exp(A, TT, n, e/2);
  assign(C, TT);
  mul(C, C, TT, n, n, n);
  assign(C, TT);
  if (e % 2 == 1){
    mul(C, A, TT, n, n, n);
    assign(C, TT);
  }
}


int main(){
  int Casos;
  cin >> Casos;
  for (int Caso=1; Caso<=Casos; ++Caso){
    int n, m, k, d;
    if (!(cin >> n >> m >> k >> d)) break;
    for (int i=0; i<n; ++i){
      g[i].clear();
      g[i].push_back(i);
      day[i] = -1;
    }
    while (m--){
      int u, v; cin >> u >> v;
      g[u].push_back(v), g[v].push_back(u);
    }

    //find day of sum for each node
    queue<int> q;
    day[k] = 0;
    q.push(k);
    while (q.size()){
      int u = q.front(); q.pop();
      foreach(edge, g[u]){
        int v = *edge;
        if (day[v] == -1){
          day[v] = !day[u];
          q.push(v);
        }
      }
    }

    //find odd/even matrices
    for (int j=0; j<n; ++j){
      for (int i=0; i<n; ++i){
        odd[i][j] = even[i][j] = 0;
      }
      foreach(edge, g[j]){
        int i = *edge;
        if (day[j] == 0){
          even[i][j] = 1;
        }else{
          odd[i][j] = 1;
        }
      }
      even[j][j] = odd[j][j] = 1;
    }

    //D("odd"); For(i, 0, n){ For(j, 0, n) printf("%d ", odd[i][j]); printf("\n"); }

    //D("even"); For(i, 0, n){ For(j, 0, n) printf("%d ", even[i][j]); printf("\n"); }



    mul(odd, even, C, n, n, n);
    exp(C, T, n, d/2);
    assign(C, T);

    if (d % 2 == 1){
      mul(C, odd, T, n, n, n);
      assign(C, T);
    }

    D("C"); For(i, 0, n){ For(j, 0, n) printf("%d ", C[i][j]); printf("\n"); }

    for (int j=0; j<n; ++j){
      ans[0][j] = 0;
    }
    ans[0][k] = 1;

    mul(ans, C, T, 1, n, n);

    printf("Case %d:", Caso);
    for (int j=0; j<n; ++j){
      printf(" %d", T[0][j]);
    }
    printf("\n");
  }
  return 0;
}
