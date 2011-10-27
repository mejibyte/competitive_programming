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

const int MAXN = 15;
const int MAXR = 105;
const int MAXS = MAXR * MAXR;

int a[MAXN];
int sum[1 << MAXN];
int popcount[1 << MAXN];
int memo[MAXR][1 << MAXN];
vector<int> masks[MAXS];

int n;

bool f(int r, int c, int mask){
  //printf("f(r=%d, c=%d, mask=%x, sum[mask]=%d)\n", r, c, mask, sum[mask]);
  if (sum[mask] != r * c) return false;

  // r * c == sum[mask]
  if (popcount[mask] == 1) return true;
  

  if (memo[r][mask] != -1) return memo[r][mask];

  for (int i=1; i<r; ++i){
    int rleft = i, rright = r - i;
    //printf("rleft = %d, rright = %d\n", rleft, rright);
   
    const vector<int> &optionsleft = masks[ rleft * c ];
    for (int k = 0; k < optionsleft.size(); ++k){
      int lsubset = optionsleft[k];
      if (~mask & lsubset) continue;
      int rsubset = mask & ~lsubset;

      //printf("lsubset = %X, rsubset = %X\n", lsubset, rsubset);
      assert((lsubset | rsubset) == mask);
      assert((lsubset & rsubset) == 0);
      assert(sum[lsubset] == rleft * c);

      if (sum[rsubset] == rright * c){
	bool maybe = f(rleft, c, lsubset) && f(rright, c, rsubset);
	if (maybe){
	  memo[r][mask] = memo[c][mask] = 1;
	  return 1;
	}
      }
    }
  }

  for (int j=1; j<c; ++j){
    int cleft = j, cright = c - j;
    const vector<int> &optionsleft = masks[ cleft * r ];
    for (int k = 0; k < optionsleft.size(); ++k){
      int lsubset = optionsleft[k];
      if (~mask & lsubset) continue;
      int rsubset = mask & ~lsubset;
      assert((lsubset | rsubset) == mask);
      assert((lsubset & rsubset) == 0);
      assert(sum[lsubset] == cleft * r);
	
      if (sum[rsubset] == cright * r){
	bool maybe = f(r, cleft, lsubset) && f(r, cright, rsubset);
	if (maybe){
	  memo[r][mask] = memo[c][mask] = 1;
	  return 1;
	}
      }
    }
  }


  
  memo[r][mask] = memo[c][mask] = 0;
  return 0;
}

int main(){
  int Case = 0;
  while (scanf("%d", &n) == 1){
    if (n == 0) break;
    printf("Case %d: ", ++Case);
    
    int r, c;
    scanf("%d %d", &r, &c);
    for (int i = 0; i < n; ++i){
      scanf("%d", &a[i]);
    }

    for (int i = 0; i <= r * c; ++i){
      masks[i].clear();
    }

    for (int mask = 0; mask < (1 << n); ++mask){
      sum[mask] = popcount[mask] = 0;
      for (int k = 0; k < n; ++k){
	if (mask & (1 << k)){
	  sum[mask] += a[k];
	  popcount[mask]++;
	}
      }

      masks[sum[mask]].push_back(mask);

      for (int i = 0; i < MAXR; ++i){
	memo[i][mask] = -1;
      }
    }
    
    // for (int mask = 0; mask < (1 << n); ++mask){
    //   printf("Mask = %X\n", mask);
    //   printf("    popcount = %d\n", popcount[mask]);
    //   printf("    sum = %d\n", sum[mask]);
    // }

    bool ans = f(r, c, (1 << n) - 1);
    printf("%s\n", ans ? "Yes" : "No");
  }
  return 0;
}
