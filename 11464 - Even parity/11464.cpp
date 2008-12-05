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

bool p[15][15];
bool backup[15][15];
bool can_change[15][15];
int n;

#define inside(i, j) (0 <= (i) && (i) < n && 0 <= (j) && (j) < n)

void attack(int i, int j){
  if (can_change[i][j]){
    if (inside(i-1, j)) p[i-1][j] = !p[i-1][j];
    if (inside(i+1, j)) p[i+1][j] = !p[i+1][j];
    if (inside(i, j-1)) p[i][j-1] = !p[i][j-1];
    if (inside(i, j+1)) p[i][j+1] = !p[i][j+1];
  }
}


int main(){
  int cases;
  scanf("%d", &cases);
  for (int C=1; C<=cases; C++){

    if (scanf("%d", &n) != 1) return 0;
    
    memset(p, 0, sizeof p);
    for (int i=0; i<n; ++i){
      for (int j=0; j<n; ++j){
	int x;
	scanf("%d", &x);
	can_change[i][j] = true;
	if (x)  attack(i, j);
	can_change[i][j] = !x;
      }
    }

    memcpy(backup, p, sizeof p);

    int ans = INT_MAX;
    //Brute-force the subset of cells to change in the first row
    for (int subset=0; subset<(1<<n); ++subset){
      memcpy(p, backup, sizeof backup);
      int cnt = 0;
      for (int j=0; j<n; ++j){
	if (subset & (1 << j)){
	  attack(0, j);
	  cnt++;
	}
      }

      //Now, deduce the moves for next rows
      for (int i=1; i<n; ++i){
	for (int j=0; j<n; ++j){
	  if (p[i-1][j]){
	    attack(i, j);
	    cnt++;
	  }
	}
      }
      
      //Let's see if this solved it.
      bool ok = true;
      for (int i=0; i<n; ++i)
	for (int j=0; j<n; ++j)
	  ok &= !p[i][j];


      if (ok) ans = min(ans, cnt);

    }
    printf("Case %d: %d\n", C, (ans < INT_MAX ? ans : -1));
  }
  return 0;
}
