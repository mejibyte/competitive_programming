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


char mat[55][55];

int di[] = {+0, +1, +1, +1};
int dj[] = {+1, +1, +0, -1};

void solve(){
  int n, k;
  cin >> n >> k;
  for (int j = n - 1; j >= 0; --j){
    for (int i = 0; i < n; ++i){
      cin >> mat[i][j];
    }
  }

  for (int i = n - 1; i >= 0; --i){
    for (int j = 0; j < n; ++j){
      if (mat[i][j] == '.') continue;
      int k = i + 1;
      while (k < n and mat[k][j] == '.') k++;
      swap(mat[i][j], mat[k - 1][j]);
    }
  }

  int winners = 0;
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; ++j){
      if (mat[i][j] == '.') continue;
      for (int d = 0; d < 4; ++d){
	int ni = i + (k - 1) * di[d];
	int nj = j + (k - 1) * dj[d];
	if (0 <= ni and ni < n and 0 <= nj and nj < n){
	  bool ok = true;
	  for (int p = 0; p < k; ++p){
	    if (mat[i + p * di[d] ][ j + p * dj[d] ] != mat[i][j]){
	      ok = false;
	      break;
	    }
	  }
	  if (ok){
	    winners |= (mat[i][j] == 'R' ? 1 : 2);
	  }
	}
      }
    }
  }
  
  // For(i, 0, n){
  //   For(j, 0, n){
  //     cout << mat[i][j];
  //   }
  //   cout << endl;
  // }cout << endl;
  string s;
  if (winners == 0){
    s = "Neither";
  }else if (winners == 1){
    s = "Red";
  }else if (winners == 2){
    s = "Blue";
  }else if (winners == 3){
    s = "Both";
  }
  printf("%s\n", s.c_str());
}

int main(){
  int T;
  cin >> T;
  for (int i = 0; i < T; ++i){
    printf("Case #%d: ", i + 1);
    solve();
  }
  return 0;
}
