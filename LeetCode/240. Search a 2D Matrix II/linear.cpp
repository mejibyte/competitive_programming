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
    Start with a cursor in the top right corner:

    x x x x c
    x x x x x
    x x x x x
    x x x x x


    If the element is larger than target, any other value that is below but in the same column
    will also be larger, so move left and try again:

    x x x c >
    x x x x >
    x x x x >
    x x x x >


    If it is larger again, same logic applies, so we move left and end up with this:

    x x c > >
    x x x > >
    x x x > >
    x x x > >

    Keep moving left as long as we are seeing larger elements. Eventually, one of
    these 3 things will happen:
    - We ran out of columns: In this case, we are done -- the element is not there,
         because the entire matrix is larger.
    - We found an element that is equal to our target: we are done -- just return true.
    - We found an element that is smaller: in this case, any other element to the left
         of where we are is also smaller, so there is no point in looking at any other
         element in this row. So move down and repeat the same logic:

    < < < > >
    x x c > >
    x x x > >
    x x x > >

    We keep moving left or down like that until eventually we find the element or
    we consume the entire matrix:

    < < < > >
    < < < > >
    x x c > >
    x x x > >

    More formally, we keep a candidate matrix with top left (r, 0) and bottom
    right (rows-1, c) where we expect the target to be. By looking at the top right
    corner, we can either discard the top row (if the top right corner element is
    smaller than target) or discard the rightmost column (if the top right corner
    element is larger than target).

    Total complexity is O(Rows + Cols).
    */

    for (int r = 0, c = cols - 1; r < rows and c >= 0; r++) {
      while (c >= 0 and m[r][c] > target) c--;
      if (c >= 0 and m[r][c] == target) return true;
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