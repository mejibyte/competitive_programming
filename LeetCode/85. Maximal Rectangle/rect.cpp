// Andrés Mejía
#include <unordered_map>
#include <unordered_set>
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

struct Item {
  int index, height;
};

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
      int rows = matrix.size();
      if (rows == 0) return 0;
      int cols = matrix[0].size();
      vector<vector<int>> height(rows, vector<int>(cols, 0));
      int best = 0;
      for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
          height[i][j] = matrix[i][j] - '0';
          if (height[i][j] == 1 and i - 1 >= 0) height[i][j] += height[i - 1][j];
        }
        best = max(best, maxHistogram(height[i]));
      }
      return best;
    }

    int maxHistogram(vector<int> v) {
      stack<Item> s;
      s.push({-1, 0});
      int best = 0;
      v.push_back(0);
      for (int i = 0; i < v.size(); ++i) {
        while (s.size() > 0 and s.top().height > v[i]) {
          int h = s.top().height;
          s.pop();
          // I can extend a rectangle of height h from [index of previous smaller rectangle, i-1].
          best = max(best, h * (i - 1 - s.top().index));
        }
        s.push({i, v[i]});
      }
      return best;
    }
};

int main() {
  Solution s;


  return 0;
}


