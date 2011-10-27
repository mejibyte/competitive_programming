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

void randomCase(int max){
  int n = random()%9+2;
  cout << n << endl;
  for (int i=0; i<n; ++i){
    int x, y;
    x = random()%(max+1) * (random()%2?-1:1);
    y = random()%(max+1) * (random()%2?-1:1);
    cout << x << " " << y << endl;
  }

}

int main(){
  for(int i=10; i--;){
    randomCase(10);
  }
  cout << 0 << endl;
  return 0;
}
