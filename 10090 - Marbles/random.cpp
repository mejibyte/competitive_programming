/*
  Problem:
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

int main(){
  int n = 100;
  int mod = 10;
  for(int i=0; i<100; ++i){
    printf("%d\n%d %d\n%d %d\n", random()%mod+1, random()%mod+1, random()%mod+1, random()%mod+1, random()%mod+1);
  }

  printf("0\n");
  return 0;
}
