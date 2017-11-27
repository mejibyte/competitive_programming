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
    bool isMatch(const string &s, const string &p, int i = 0, int j = 0) {
      if (j >= p.size()) return i >= s.size();
      bool next = i < s.size() and (s[i] == p[j] || p[j] == '.');
      if (j + 1 < p.size() and p[j + 1] == '*') {
        if (isMatch(s, p, i, j + 2)) return true;
        if (next and isMatch(s, p, i + 1, j)) return true;
      } else {
        if (!next) return false;
        return isMatch(s, p, i + 1, j + 1);
      }
      return false;
    }
};

int main() {
  Solution s;
  D(s.isMatch("aa","a"));
  D(s.isMatch("aa","aa"));
  D(s.isMatch("aaa","aa"));
  D(s.isMatch("aa", "a*"));
  D(s.isMatch("aa", ".*"));
  D(s.isMatch("ab", ".*"));
  D(s.isMatch("aab", "c*a*b"));
  D(s.isMatch("", "a*"));
  D(s.isMatch("a", "a"));
  D(s.isMatch("a", ""));
  D(s.isMatch("aaabb", ".*bb*"));
  D(s.isMatch("aaabb", ".*b*"));
  D(s.isMatch("aaabb", ".*ab*"));
  D(s.isMatch("aaabb", ".*ab"));


  return 0;
}


