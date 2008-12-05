/*
  Problem: 993 - Product of digits
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
  int c;
  for (cin >> c; c--; ){
    int n;
    cin >> n;

    if (n == 1){
      cout << 1 << endl;
      continue;
    }

    string ans = "";
    for (int i=9; i>=2; --i){
      while (n % i == 0){
        n /= i;
        ans = char(i+'0') + ans;
      }
    }

    if (n > 1){
      ans = "-1";
    }

    cout << ans << endl;
  }
  return 0;
}
