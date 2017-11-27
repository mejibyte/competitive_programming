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
    int romanToInt(string s) {
      map<char, int> value({{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}});
      int ans = 0;
      for (int i = 0; i < s.size(); ++i) {
        int add = value[s[i]];
        if (i + 1 < s.size() and value[s[i]] < value[s[i + 1]]) {
          add *= -1;
        }
        ans += add;
      }
      return ans;
    }
};

int main() {
  Solution s;
  D(s.romanToInt("I"));
  D(s.romanToInt("II"));
  D(s.romanToInt("III"));
  D(s.romanToInt("IV"));
  D(s.romanToInt("V"));
  D(s.romanToInt("VI"));
  D(s.romanToInt("VII"));
  D(s.romanToInt("VIII"));
  D(s.romanToInt("IX"));
  D(s.romanToInt("MMVI"));
  D(s.romanToInt("MCMXCIX"));
  return 0;
}


