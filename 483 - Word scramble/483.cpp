/*
  Problem: 483 - Word scramble
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
  for (string s; getline(cin, s); cout << "\n"){
    bool first = true;
    for (stringstream sin(s); sin >> s; reverse(s.begin(), s.end()), cout << (first ? "" : " ") << s, first = false);
  }
  return 0;
}
