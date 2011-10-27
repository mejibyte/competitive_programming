/*
  Problem: 10018 - Reverse and add
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
#include <list>
#include <map>
#include <set>

#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

typedef unsigned int uint;

uint invert(uint n){
  uint p = 0;
  while(n){
    p = p * 10 + n % 10;
    n = n / 10;
  }
  return p;
}

int main(){
  uint t, n;
  cin >> t;
  while (t--){
    cin >> n;
    uint ans = 0;
    while (n != invert(n)){
      ans++;
      n += invert(n);
    }
    cout << ans << " " << n << endl;
  }
  return 0;
}
