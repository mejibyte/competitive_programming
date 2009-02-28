/*
  Problem: 10573 - Geometry Paradox (UVa)
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
#define D(x) cout << #x " is " << x << endl
#define For(i, a, b) for (int i=(a); i<(b); ++i)

int main(){
  int n;
  cin >> n;
  string s;
  getline(cin, s);
  while (n-- && getline(cin, s)){
    int r1, r2;
    if (sscanf(s.c_str(), "%d %d", &r1, &r2) == 2){
      printf("%.4lf\n", 4*acos(0)*r1*r2);
    }else{
      int t;
      sscanf(s.c_str(), "%d", &t);
      printf("%.4lf\n", acos(0)*t*t/4);
    }
  }
  return 0;
}

/*
  If you are given r1 and r2, then the gray area is
  the area of the big circle minus the area of the small circles:

  pi * ((r1 + r1)² - r1² - r2²)) = 2 * pi * r1 * r2

  If you are given t, you can form a rectangular triangle where the cathetuses
  are (t/2) and k, and the hypothenuse is (r1 + r2). Then, k = (r1 - r2).
  Solve the pythagorean theorem for this triangle and you should get

  r1 * r2 = t² / 16

  Replace r1 * r2 in the formula above and you will get
  2 * pi * r1 * r2 = 2 * pi * (t² / 16) = pi * t² / 8
 */
