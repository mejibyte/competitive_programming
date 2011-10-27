/*
  Problem: 10473 - Simple Base Conversion
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

char buf[32];

int main(){
  int n;
  while (scanf("%31s", buf) == 1 && (n = strlen(buf)) > 0 && buf[0] != '-'){
    int x;
    if (n > 2 && buf[1] == 'x'){
      sscanf(buf, "%x", &x);
      printf("%d\n", x);
    }else{
      sscanf(buf, "%d", &x);
      printf("0x%X\n", x);
    }
  }
  return 0;
}
