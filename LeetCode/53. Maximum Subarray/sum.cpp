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
    int maxSubArray(vector<int>& nums) {
        assert(nums.size() > 0);
        long long best = nums[0], sum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            best = max(best, sum);
            if (sum < 0) {
                sum = 0;
            }
        }
        return best;
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


