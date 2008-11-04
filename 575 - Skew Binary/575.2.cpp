/*
  Problem: 575 - Skew simmetry (UVa)
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

  string s;
  while (cin >> s && s != "0"){
    reverse(s.begin(), s.end());
    int ans = 0;

    for (int i=0, b=1; i<s.size(); ++i, b = 2*b+1){
      ans += (s[i] - '0')*b;
    }

    cout << ans << endl;
  }

  return 0;
}
