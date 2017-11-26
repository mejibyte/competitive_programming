// Andrés Mejía
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
using namespace std;

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cerr << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

struct Event {
  enum { OPEN, CLOSE };
  int x, type, height;
  bool operator < (const Event& that) const {
    if (x != that.x) return x < that.x;
    return type < that.type;
  }
};

class Solution {
public:
    vector<pair<int, int>> getSkyline(const vector<vector<int>>& buildings) {
      int n = buildings.size();
      vector<Event> events;
      for (int i = 0; i < n; ++i) {
        const auto& b = buildings[i];
        events.push_back({b[0], Event::OPEN, b[2]});
        events.push_back({b[1], Event::CLOSE, b[2]});
      }
      sort(events.begin(), events.end());

      multiset<int> h;
      vector<pair<int, int>> ans;
      int last = 0;
      for (int i = 0; i < events.size(); ++i) {
        // Process i-th event.
        if (events[i].type == Event::OPEN) {
          h.insert(events[i].height);
        } else if (events[i].type == Event::CLOSE) {
          auto it = h.find(events[i].height);
          assert(it != h.end());
          h.erase(it);
        }

        // Make sure we've processed all events with the same X before computing the height at X.
        if (i + 1 < events.size() && events[i].x == events[i + 1].x) {
          continue;
        }

        // Compute height.
        int height = *--h.end();
        if (height != last) {
          ans.push_back(make_pair(events[i].x, height));
        }
        last = height;
      }
      return ans;
    }
};

int main(){

    // multiset<int> x;
    // x.insert(1);
    // x.insert(1);
    // x.insert(2);
    // x.insert(2);
    // x.insert(2);
    // for (auto d : x) D(d);
    // multiset<int>::iterator i = x.find(2);
    // x.erase(i);
    // D("next");
    // for (auto d : x) D(d);
    // return 0;

    Solution s;
    auto ans = s.getSkyline({ {2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8} });
    for (auto p : ans) {
      cout << p.first << " " << p.second << endl;
    }
    cout << endl;

    ans = s.getSkyline({ {2, 9, 10}, {2, 9, 10}, {3, 9, 10}, {3, 9, 8}, {4, 5, 5} });
    for (auto p : ans) {
      cout << p.first << " " << p.second << endl;
    }
    //for (auto k : ans) D(k);
    return 0;
}
