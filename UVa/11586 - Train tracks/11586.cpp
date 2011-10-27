/*
  Problem:
  Andrés Mejía-Posada (andmej@gmail.com)
 */
using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <numeric>
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

int main(){
  int casos;
  cin >> casos;
  string s;
  getline(cin, s);
  while (casos--){
    int m = 0, f = 0;
    getline(cin, s);
    stringstream sin(s);
    while (sin >> s){
      if (s[0] == 'M') m++; else f++;
      if (s[1] == 'M') m++; else f++;
    }
    if (m % 2 == 0 && f % 2 == 0){
      cout << "LOOP" << endl;
    }else{
      cout << "NOT LOOP" << endl;
    }
  }
  return 0;
}
