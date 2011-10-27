/*
  Problem: 11088 - End up with More Teams
  Author: Andrés Mejía-Posada 
  (http://blogaritmo.factorcomun.org)

  Accepted
 */

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
using namespace std;

#define D(x) cout << #x " is " << x << endl
#define bit(i, n) (n & (1 << i))

int memo[1<<15], x[15], n;

/*
  Returns the maximum amount of teams that can be made using
  teams set on on bitwise mask avail. At each step, I try to
  build a new team using the first available person, or igno-
  re that person completely.
 */
int best(int avail){
  int &ans = memo[avail];
  if (ans == -1){
    ans = 0;
    for (int i=0; i<n; ++i)
      if (bit(i, avail)){
	ans = max(ans, best(avail & ~(1 << i))); //Ignore this dogg
	for (int j=i+1; j<n; ++j)
	  if (bit(j, avail))
	    for (int k=j+1; k<n; ++k)
	      if (bit(k, avail))
		if(x[i] + x[j] + x[k] >= 20)
		  ans = max(ans, 1 + best(avail & ~(1 << i) & ~(1 << j) & ~(1 << k))); //Make team (i, j, k).
	break;
      }
  }
  //printf("best(%X) = %d\n", avail, ans);
  return ans;
}

int main(){
  int pizza = 1;
  while (scanf("%d", &n) == 1 && n){
    for (int i = 0; i<n; ++i) scanf("%d", &x[i]);
    
    memset(memo, -1, sizeof memo);
    printf("Case %d: %d\n", pizza++, best((1 << n) - 1));
  }

  return 0;
}
