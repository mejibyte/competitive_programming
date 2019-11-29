// Reimplementing this from scratch on 11-29-2019
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
#include <unordered_set>
#include <unordered_map>
using namespace std;

/*
- Find pair (i, j) with i <= j such that j-i+1 is minimum and sum[i,j] >= k
- Let's assume we have fixed j
   - Find largest i such that sum[i,j] >= k.
   - If we find such a solution, it is not worth trying the same i with a larger j, because length will be longer.
*/

class Solution {
public:
  int shortestSubarray(vector<int> A, int K) {
    const int inf = numeric_limits<int>::max();
    int sum = 0, best = inf;
    for (int j = 0, i = 0; j < A.size(); ++j) {
      // Here, sum == sum[0,j)
      // Insert new element j. If sum[0,j) is smaller than any other one before, then
      // those are no longer needed, so we can pop them.
      while (q.size() > 0 and sum <= q.back().first) {
        q.pop_back();
      }
      q.push_back({sum, j});

      // Here, q contains all <sum[0,i), i> for all i <= j sorted by ascending sum and i.
      // Find the smallest i such that sum[0,j] - sum[0,i) >= K. If it works, we will
      // never use it again with a larger j, so we can pop it and try again with the second
      // largest i.
      while (q.size() > 0 and sum + A[j] - K >= q.front().first) {
        best = min(best, j - q.front().second + 1);
        q.pop_front();
      }
      sum += A[j];
    }
    return best == inf ? -1 : best;
  }

  deque<pair<int, int>> q; // sum[i], i

};

#ifdef LOCAL
int main() {
  Solution s;
  assert(s.shortestSubarray({1}, 1) == 1);
  assert(s.shortestSubarray({1, 2}, 4) == -1);
  assert(s.shortestSubarray({2,-1, 2}, 3) == 3);
  assert(s.shortestSubarray({10,-1, 11}, 11) == 1);
  assert(s.shortestSubarray({-1, -1, -1}, 0) == -1);
  //cout << s.shortestSubarray({10,-1, 11}, 11) << endl;
  assert(s.shortestSubarray({84,-37,32,40,95}, 167) == 3);

  return 0;
}
#endif