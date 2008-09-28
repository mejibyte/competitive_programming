/*
  Problem: 11494 - Queen
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
  int a, b, c, d;
  while (cin >> a >> b >> c >> d && (a+b+c+d)){
    if (a == c && b == d) cout << "0\n";
    else if (a == c || b == d || ((a-c==b-d) || (a-c==d-b))) cout << "1\n"; //Same row, column or diagonal
    else cout << "2\n";
  }
  return 0;
}
