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

using namespace std;

template <class T> string toStr(const T &x){
stringstream s; s << x; return s.str();
}

template <class T> int toInt(const T &x){
stringstream s; s << x; int r; s >> r; return r;
}

#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define D(x) cout << #x " = " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y, double tol = EPS){
  return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

const int MAXN = 105;

int A[MAXN], B[MAXN];

vector<int> g[MAXN];

bool segundo_de_mayor_a_menor(pair<int, int> a, pair<int, int> b){
  if (a.second != b.second) return a.second > b.second;
  return a.first < b.first;
}


pair<int, int> f(int u, int dad = -1){
  vector< pair<int, int> > p;
  for (int i = 0; i < g[u].size(); ++i){
    int v = g[u][i];
    if (v == dad) continue;

    p.push_back( f(v, u) );
  }
  
  sort(p.begin(), p.end(), segundo_de_mayor_a_menor);
 
  int total = A[u];
  int tengo = A[u] - B[u];
  for (int i = 0; i < p.size(); ++i){
    if (tengo > p[i].first){
      tengo -= p[i].first - p[i].second;
    }else{
      total += p[i].first - tengo;
      tengo = p[i].second;
    }
  }
  //printf(" f(u=%d) = <%d, %d>\n", u, total, tengo);
  return make_pair(total, tengo);
}

int main(){
  int n, Caso = 1;
  while (cin >> n){
    if (n == 0) break;
    cout << "Case " << Caso++ << ": ";

    for (int i = 0; i < n; ++i){
      int x, y, z;
      cin >> x >> y >> z;
      A[i] = x;
      B[i] = y + z;
      A[i] = max(A[i], B[i]);

      g[i].clear();
    }

    for (int i = 0; i < n - 1; ++i){
      int u, v;
      cin >> u >> v;
      u--, v--;
      g[u].push_back(v);
      g[v].push_back(u);
    }

    //for (int i = 0; i < n; ++i){
    //  printf("Nodo %d: A = %d, B = %d\n", i, A[i], B[i]);
    //}
    
    int ans = INT_MAX;
    for (int i = 0; i < n; ++i){

      pair<int, int> p = f(i);
      //printf("Empezando en %d: <%d, %d>\n", i, p.first, p.second);
      

      ans = min(ans, p.first);
      
    }
    
    cout << ans << endl;
  }
  return 0;
}
