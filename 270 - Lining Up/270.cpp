/*
  Problem: 270 - Lining up
  Andrés Mejía-Posada (andmej@gmail.com)

  Time limit exceeded.
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

#define D(x) cout << #x " is " << x << endl

struct point{
  int x, y;
  point(int x=0, int y=0) : x(x), y(y) {}
};

inline void simplify(pair<int, int> &p){
  #define x first
  #define y second
  if (p.y == 0){
    p.x = 1;
    return;
  }
  if (p.x == 0){
    p.y = 1;
    return;
  }
  int sign = ((p.x<0)^(p.y<0) ? -1 : 1);
  if (p.x < 0) p.x *= -1;
  if (p.y < 0) p.y *= -1;
  int g = __gcd(p.x, p.y);
  if (g) p.x /= g, p.y /= g;
  p.x *= sign;
  #undef x
  #undef y
}

char buf[512];

int main(){
  int cases;
  fgets(buf, 512, stdin);
  sscanf(buf, "%d", &cases);
  fgets(buf, 512, stdin);
  while (cases--){
    vector<point> p;
    while (fgets(buf, 512, stdin) != NULL && strcmp(buf, "\n")){
      point _;
      sscanf(buf, "%d %d", &_.x, &_.y);
      p.push_back(_);
    }

    int x = 0;
    map<pair<int, int>, int> cnt;
    const int n = p.size();
    for (int i=0; i<n; ++i){
      for (int j=i+1; j<n; ++j){
        pair<int, int> slope(p[j].y - p[i].y, p[j].x - p[i].x);
        simplify(slope);
        x = max(x, ++cnt[slope]);
      }
    }

    printf("%d\n", (int)((1 + sqrt(1 + 8*x))/2));
    if (cases > 0) puts("");
  }
  return 0;
}
