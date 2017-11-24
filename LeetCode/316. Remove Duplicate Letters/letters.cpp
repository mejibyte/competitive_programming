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
    // The idea is to find the first character of the answer.
    // (It is the smallest char that still has all others characters after it.)
    // We then delete everything before that character, all other copies of that character
    // and solve the same problem recursively (with one less character).
    string removeDuplicateLetters(string s) {
      if (s == "") return s;
      if (s.size() == 1) return s;

      set<char> need;
      for (char c : s) {
        need.insert(c);
      }

      int best = -1;
      set<char> seen;
      for (int i = s.size() - 1; i >= 0; --i) {
        seen.insert(s[i]);
        if (seen.size() == need.size()) {
          if (best == -1 or s[i] <= s[best]) {
            best = i;
          }
        }
      }
      assert(best >= 0);
      char c = s[best];
      s = s.substr(best + 1);
      for (size_t at = s.find(c); at != string::npos; at = s.find(c, at)) {
        s.erase(at, 1);
      }
      return c + removeDuplicateLetters(s);
    }
};

int main(){
    Solution s;
    D(s.removeDuplicateLetters("abacb"));
    //D(s.removeDuplicateLetters("bcabc"));
    //D(s.removeDuplicateLetters("cbacdcbc"));
    return 0;
}
