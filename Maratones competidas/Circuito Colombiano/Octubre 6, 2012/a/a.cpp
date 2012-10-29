// Andrés Mejía
// Accepted
using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <bitset>
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

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

struct Rectangle {
    int x1, y1, x2, y2;
    Rectangle(){}
    Rectangle(int _x1, int _y1, int _x2, int _y2) {
        x1 = min(_x1, _x2);
        x2 = max(_x1, _x2);
        y1 = min(_y1, _y2);
        y2 = max(_y1, _y2);
        assert(x1 <= x2);
        assert(y1 <= y2);
    }
    
    bool has_area() const {
        return x1 < x2 and y1 < y2;
    }
};

vector<int> all;

int compress(int what) {
    int ans = lower_bound(all.begin(), all.end(), what) - all.begin();
    assert(0 <= ans and ans < all.size());
    assert(all[ans] == what);
    return ans;
}

const int MAXN = 505;
bool visited[MAXN][MAXN];
Rectangle cookie;

void visit(int x, int y) {
    if (x < cookie.x1 or y < cookie.y1) return;
    if (x >= cookie.x2 or y >= cookie.y2) return;
    if (visited[x][y]) return;
    visited[x][y] = true;
    visit(x - 1, y);
    visit(x + 1, y);
    visit(x, y - 1);
    visit(x, y + 1);
}

int main(){
  //freopen("cookie", "r", stdin);
  int runs; cin >> runs;
  while (runs--) {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      cookie = Rectangle(x1, y1, x2, y2);
      all.clear();
      all.push_back(x1);
      all.push_back(y1);
      all.push_back(x2);
      all.push_back(y2);
      int n; cin >> n;
      
      vector<Rectangle> chips;
      for (int i = 0; i < n; ++i) {
          cin >> x1 >> y1 >> x2 >> y2;
          Rectangle chip(x1, y1, x2, y2);
          // clip to cookie area
          chip.x1 = max(chip.x1, cookie.x1);
          chip.x2 = min(chip.x2, cookie.x2);
          chip.y1 = max(chip.y1, cookie.y1);
          chip.y2 = min(chip.y2, cookie.y2);
          
          if (chip.has_area()) {
              all.push_back(chip.x1);
              all.push_back(chip.y1);
              all.push_back(chip.x2);
              all.push_back(chip.y2);
              chips.push_back(chip);
          }
      }
      sort(all.begin(), all.end());
      all.resize(unique(all.begin(), all.end()) - all.begin());
      cookie.x1 = compress(cookie.x1);
      cookie.x2 = compress(cookie.x2);
      cookie.y1 = compress(cookie.y1);
      cookie.y2 = compress(cookie.y2);
      for (int i = 0; i < chips.size(); ++i) {
          chips[i].x1 = compress(chips[i].x1);
          chips[i].x2 = compress(chips[i].x2);
          chips[i].y1 = compress(chips[i].y1);
          chips[i].y2 = compress(chips[i].y2);
      }
      assert(cookie.x2 < 500 and cookie.y2 < 500);
      
      memset(visited, false, sizeof visited);
      for (int i = 0; i < chips.size(); ++i) {
          const Rectangle &c = chips[i];
          for (int x = c.x1; x < c.x2; ++x) {
              for (int y = c.y1; y < c.y2; ++y) {
                  visited[x][y] = true;
              }
          }
      }
      
      int ans = 0;
      for (int x = cookie.x1; x < cookie.x2; ++x) {
          for (int y = cookie.y1; y < cookie.y2; ++y) {
              if (!visited[x][y]) {
                  ans++;
                  visit(x, y);
              }
          }
      }
      cout << ans << endl;
  }
  cout << endl;
  return 0;
}