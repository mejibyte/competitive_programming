#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

#define DEBUG false
#define dprintf DEBUG&& printf

class Solution {
 public:
  bool searchMatrix(vector<vector<int>>& m, int target) {
    int rows = m.size();
    if (rows == 0) return false;
    int cols = m[0].size();
    if (cols == 0) return false;

    /*
    Same as linear.cpp but starting in bottom left corner. See linear.cpp for
    detailed explanation on why this works.
    */

    int r = rows - 1, c = 0;
    while (r >= 0 and c < cols) {
      if (m[r][c] > target) r--;
      else if (m[r][c] < target) c++;
      else return true;
    }
    return false;
  }
};

#ifdef LOCAL
int main() {
  Solution s;

  return 0;
}
#endif