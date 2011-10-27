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

const int MAXN = 55;
vector<int> d[2 * MAXN];
vector<int> e[2 * MAXN];

#define minimize(x, y) if ((y) < (x)) (x) = (y)

bool startsWith(vector<int> a, vector<int> b){
  assert(b.size() <= a.size());
  for (int i = 0; i < b.size(); ++i){
    if (a[i] != b[i]) return false;
  }
  return true;
}

void DV(vector<int> v){
  for (int i = 0; i < v.size(); ++i){
    cout << v[i] << " ";
  }
  cout << endl;
}

int reflect(vector<int> a){
  if (a.size() == 1) return 0;
  int ans = a.size();
  D("a");
  DV(a);

  int half = (a.size() + 1) / 2;
  
  for (int i = half; i < a.size(); ++i){
    vector<int> l;
    for (int j = 0; j < half; ++j) l.push_back(a[i]);

    vector<int> l_reversed = l;
    reverse(l.begin(), l.end());
    
    vector<int> t;

    t = l;
    for (int k = 0; k < l_reversed.size(); ++k) t.push_back(l_reversed[k]);
    
    assert(t.size() >= a.size());
    if (startsWith(t, a)){
      minimize(ans, t.size() - a.size());
    }

    t = l;
    for (int k = 1; k < l_reversed.size(); ++k) t.push_back(l_reversed[k]);
    assert(t.size() >= a.size());
    if (startsWith(t, a)){
      minimize(ans, t.size() - a.size());
    }
    

  }
  return ans;
}

void solve(){
  int n;
  cin >> n;
  for (int i = 0; i < 2 * n; ++i){
    d[i].clear();
    e[i].clear();
  }
  
  for (int i = 0; i < n; ++i){
    for (int j = 0; j <= i; ++j){
      int x;
      cin >> x;
      d[i].push_back(x);
    }
  }
  for (int i = n-2; i >= 0; --i){
    for (int j = 0; j <= i; ++j){
      int x;
      cin >> x;
      d[2*n-2-i].push_back(x);
    }
  }

  // for (int i = 0; i < 2 * n; ++i){
  //   for (int j = 0; j < d[i].size(); ++j){
  //     cout << d[i][j] << " ";
  //   }
  //   cout << endl;
  // }

  vector<int> seen(2*n, 0);
  for (int j = 0; j < n; ++j){
    int s = j + 1;
    for (int i = (n - 1) - j; i <= (n - 1) + j; i += 2){
      e[j].push_back( d[i][seen[i]++] );
    }
  }

  for (int j = n - 2; j >= 0; --j){
    int s = j + 1;
    for (int i = (n - 1) - j; i <= (n - 1) + j; i += 2){
      e[2*n -2 - j].push_back( d[i][seen[i]++] );
    }
  }

 
  // for (int i = 0; i < 2*n; ++i){
  //   for (int j = 0; j < e[i].size(); ++j){
  //     cout << e[i][j] << " ";
  //   }
  //   cout << endl;
  // }

  int max_a = -1, max_b = -1;
  for (int i = 0; i < 2*n; ++i){
    max_a = max(max_a, reflect(d[i]));
    max_b = max(max_b, reflect(e[i]));
  }
  D(max_a), D(max_b);
  int add = max_a + max_b;
  int ans = 0;
  
  n = 2*n + 1;
  for (int i = 0; i < add; ++i){
    ans += n;
    n += 2;
  }
  cout << ans << endl;
}

int main(){
  int T;
  cin >> T;
  for (int i = 0; i < T; ++i){
    printf("Case #%d: ", i);
    solve();
  }
  return 0;
}
