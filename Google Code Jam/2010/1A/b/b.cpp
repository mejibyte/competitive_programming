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

const int oo = INT_MAX / 2;

#define minimize(x, y) if ((y) < (x)) (x) = (y)


int a[105];

int dp[105][256];

int D, I, M, n;

inline int inserts(int a, int b){
  if (b < a) swap(a, b);
  int diff = b - a;
  if (diff == 0) return 0; 
  if (M == 0) return oo;
  return ((diff - 1) / M) * I;
}

void solve(){
  scanf("%d%d%d%d", &D, &I, &M, &n);
  for (int i = 0; i < n; ++i){
    scanf("%d", a + i);
  }

  for (int k = 0; k < 256; ++k){
    dp[0][k] = 0;
  }

  for (int i = 1; i <= n; ++i){
    int item = a[i - 1];
    for (int k = 0; k < 256; ++k){
      dp[i][k] = oo;
      int extra = abs(k - item);
      for (int j = i - 1; j >= 0; --j){
	int deleted = i - j - 1;
	for (int p = 0; p < 256; ++p){	  
	  minimize(dp[i][k], extra + inserts(p, k) + deleted * D + dp[j][p]);
	}
      }
    }
  }

  // for (int i = 0; i <= n; ++i){
  //   for (int k = 0; k < 16; ++k){
  //     printf("dp[%d][%d] = %d\n", i, k, dp[i][k]);    
  //   }
  // }

  int ans = oo;
  for (int k = 0; k < 256; ++k){
    minimize(ans, dp[n][k]);
  }
  printf("%d\n", ans);  
}


int main(){
  int T;
  scanf("%d", &T);
  for (int i = 0; i < T; ++i){
    printf("Case #%d: ", i + 1);
    solve();
  }
  return 0;
}
