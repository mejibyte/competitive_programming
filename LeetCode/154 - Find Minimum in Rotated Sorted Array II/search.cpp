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

class Solution {
public:
    int findMin(vector<int>& nums) {
      int i = find_min(nums, 0, nums.size() - 1);
      return nums[i];
    }
private:

  // Returns index of the min element in the given rotated sorted array.
  // l and r are the indexes where the min element is guaranteed to be
  // (so the first call should be find_min(array, 0, array.size()-1)).
  int find_min(const vector<int>& array, int l, int r) {
    assert(l <= r);
    if (l == r) return l;
    int left_length = (r - l + 1) / 2;
    assert(left_length >= 1);
    int a = array[l + left_length - 1]; // last element in left half.
    int b = array[r]; // last element in right half.
    if (a < b) {
      // min is guaranteed to be in the left half, because if it were in the right half that would
      // imply b <= a which is a contradiction.
      return find_min(array, l, l + left_length - 1);
    }
    if (b < a) {
      // min is guaranteed to be in the right half, because if it were in the left half that would
      // imply a <= b which is a contradiction.
      return find_min(array, l + left_length, r);
    }
    assert(a == b);
    // Too bad, we don't have enough info to discard half of the array but we can discard one
    // element. We need to be careful in cases like "1 1 1 1 2 1" where we want the last 1!
    if (array[l] < array[r]) {
      return find_min(array, l, r - 1);
    }
    if (array[l] > array[r]) {
      return find_min(array, l + 1, r);
    }
    assert(array[l] == array[r]);
    if (array[r - 1] > array[r]) {
      return find_min(array, l + 1, r);
    }
    return find_min(array, l, r - 1);
  }
};

int main(){
    Solution s;
    cout << s.search({2, 4, 5, 6, 7, 7, 1, 1, 1, 1, 1, 2, 2}, 1) << endl;
    return 0;
}
