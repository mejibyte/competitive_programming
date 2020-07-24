// https://leetcode.com/problems/k-th-smallest-prime-fraction/
// TLE
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <iterator>
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
#include <numeric>
#include <list>
#include <map>
#include <set>
using namespace std;

#ifdef LOCAL
#define DEBUG true
#else
#define DEBUG false
#endif
#define dprintf DEBUG && printf


class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
      int rows = matrix.size();
      if (rows == 0) return false;
      int cols = matrix[0].size();
      if (cols == 0) return false;

      int low = 0, high = rows * cols - 1;
      while (low < high) {
        int mid = low + (high - low) / 2;
        int r = mid / cols;
        int c = mid % cols;
        if (matrix[r][c] < target) {
          low = mid + 1;
        } else {
          high = mid;
        }
      }
      assert(low == high);
      return matrix[low / cols][low % cols] == target;
    }
};

#ifdef LOCAL
int main() {
  Solution s;

  return 0;
}
#endif