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
    // O(n) - Kadane's algorithm
    // int maxSubArray(vector<int>& nums) {
    //     assert(nums.size() > 0);
    //     long long best = nums[0], sum = 0;
    //     for (int i = 0; i < nums.size(); ++i) {
    //         sum += nums[i];
    //         best = max(best, sum);
    //         if (sum < 0) {
    //             sum = 0;
    //         }
    //     }
    //     return best;
    // }

    int maxSubArray(vector<int>& nums) {
        return maxSubArray(nums.data(), nums.size());
    }

private:
    // O(n log n) using divide and conquer.
    long long maxSubArray(int *p, int n) {
        assert(n > 0);
        if (n == 1) return *p;
        int half = n / 2;
        assert(half > 0);
        assert(n - half > 0);

        long long best = max(maxSubArray(p, half), maxSubArray(p + half, n - half));

        long long maxPrefix = LLONG_MIN, prefixSum = 0;
        long long maxSuffix = LLONG_MIN, suffixSum = 0;
        for (int i = half - 1; i >= 0; --i) {
            prefixSum += p[i];
            maxPrefix = max(maxPrefix, prefixSum);
        }
        for (int i = half; i < n; ++i) {
            suffixSum += p[i];
            maxSuffix = max(maxSuffix, suffixSum);
        }
        return max(best, maxPrefix + maxSuffix);

    }
};

int main(){
  int x;
  vector<int> v;
  while (cin >> x) {
    v.push_back(x);
  }
  Solution s;
  cout << s.maxSubArray(v) << endl;
  return 0;
}


