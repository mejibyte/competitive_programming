/*
  Problem: 10327 - Flip sort (UVa)
  Author: Andrés Mejía-Posada
  (http://blogaritmo.factorcomun.org)

*/

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

const int N = 1000;
int a[N];

void randomTestCase(){
  int n = 1000;
  printf("%d\n", n);
  for (int i=0; i<n; ++i){
    printf("%s%d", i ? " " : "", random() % (1<<10));
  }
  printf("\n");
  exit(0);
}


int main(){
  //randomTestCase();

  for (int n; scanf("%d", &n) == 1; ){
    for (int i=0; i<n; ++i){
      scanf("%d", a+i);       
    }
    int ans = 0;
    for (int i=0; i<n; ++i){
      for (int j=i+1; j<n; ++j){
	ans += a[i] > a[j];
      }	
    }
    printf("Minimum exchange operations : %d\n", ans);
    
  }
  return 0;
}
