// Stolen from http://blog.vudduu.com/2011/12/acm-icpc-latin-america-2011-b-ball.html

/* 
 * @author: vudduu - Edwin Guzman
 * @problem: Problem B - Ball Stacking
 * @contest: ACM ICPC Latin America Regional 2011
 */
#include <iostream>
#include <sstream>
#include <utility>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <functional>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <set>
#include <stdio.h>
#include <string.h>
using namespace std;

#define FOR(i,a,b)  for(int i=(a),_##i=(b);i<_##i;++i)
#define F(i,a)      FOR(i,0,a)
#define ALL(x)      x.begin(),x.end()
#define PB          push_back
#define MP          make_pair
#define S           size()
typedef long long   LL;

LL DP[1002][1002];

int main(){
 int n, x;
 scanf("%d", &n);
 while(n){
  LL r = 0LL, aux, now_inc;
  for(int i=1; i<=n ;i++){
   DP[i][n-i+2] = 0LL;
   for(int j=1; j<=i ;j++){
    x = i-j+1;
    scanf("%lld", &aux);
    DP[x][j] = aux + DP[x][j-1] + DP[x-1][j] - DP[x-1][j-1];
    r = max(r, DP[x][j]);
   }
  }
  for(int i=1; i<=n ;i++){
   for(int j=n-i+1; j>=1 ;j--){
    now_inc = DP[i][j] - DP[i][j-1];
    r = max(r, DP[i][j] + DP[i-1][j+1]);
    DP[i][j] = max( max(DP[i-1][j+1] + now_inc, now_inc), max(DP[i][j+1] + now_inc, DP[i-1][j]) );
   }
  }
  printf("%lld\n", r);
  scanf("%d", &n);
 }
}
