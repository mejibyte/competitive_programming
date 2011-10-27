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

const int MOD = 1000000007;
const int MAXN = 35;

typedef vector< vector<long long> > matrix;

vector<int> g[MAXN];
int day[MAXN];

matrix mul(const matrix &A, const matrix &B){
  int p = A.size();
  int q = A[0].size();
  int r = B[0].size();
  matrix C(p, vector<long long>(r, 0));
  for (int i=0; i<p; ++i){
    for (int j=0; j<r; ++j){
      C[i][j] = 0;
      for (int k=0; k<q; ++k){
        C[i][j] += (A[i][k] * B[k][j]) % MOD;
        C[i][j] %= MOD;
      }
    }
  }
  return C;
}



matrix exp(const matrix &A, int e){
  int n = A.size();
  if (e == 0){
    matrix C(n, vector<long long>(n, 0));
    for (int i=0; i<n; ++i){
      C[i][i] = 1;
    }
    return C;
  }

  if (e == 1){
    return A;
  }

  matrix B = exp(A, e / 2);
  B = mul(B, B);
  if (e % 2 == 1){
    B = mul(B, A);
  }
  return B;
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

    matrix odd(n, vector<long long>(n));
    matrix even(n, vector<long long>(n));
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

    matrix C = mul(odd, even);
    C = exp(C, d / 2);
    if (d % 2 == 1){
      C = mul(C, odd);
    }

    //D("C"); For(i, 0, n){ For(j, 0, n) printf("%d ", C[i][j]); printf("\n"); }

    matrix ans(1, vector<long long>(n));

    for (int j=0; j<n; ++j){
      ans[0][j] = 0;
    }
    ans[0][k] = 1;

    C = mul(ans, C);

    printf("Case %d:", Caso);
    for (int j=0; j<n; ++j){
      printf(" %d",(int) C[0][j]);
    }
    printf("\n");
  }
  return 0;
}
