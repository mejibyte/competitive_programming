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


// "ADOBECODEBANC", "ABC"


class Solution {
public:
    string minWindow(string s, string t) {
      unordered_map<char, int> need, seen;
      int covered = 0;

      for (char k : t) need[k]++;
      string best = s + "*";
      for (int i = 0, j = 0; j < s.size(); ++j) {
        if (seen[s[j]] < need[s[j]]) {
          covered++;
        }
        seen[s[j]]++;

        for (; covered >= t.size() and i <= j; i++) {
          if (j - i + 1 < best.size()) {
            best = s.substr(i, j - i + 1);
          }

          seen[s[i]]--;
          if (seen[s[i]] < need[s[i]]) {
            covered--;
          }
        }
      }
      if (best.size() > s.size()) return "";
      return best;
    }
};

int main() {
  Solution s;
  D(s.minWindow("ADOBECODEBANC", "ABC"));
  D(s.minWindow("ADOBECODEBANC", "X"));
  D(s.minWindow("A", "AA"));
  D(s.minWindow("AABA", "AA"));
  D(s.minWindow("bba", "ab"));
  D(s.minWindow("bba", "abb"));


  return 0;
}


