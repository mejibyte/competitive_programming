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

  int kmp(const string &needle, const char* haystack, int haystack_size) {
    // Precompute border function
    int m = needle.size();
    vector<int> border(m);
    border[0] = 0;
    for (int i = 1; i < m; ++i) {
      border[i] = border[i - 1];
      while (border[i] > 0 and needle[i] != needle[border[i]]) {
         border[i] = border[border[i] - 1];
      }
      if (needle[i] == needle[border[i]]) border[i]++;
    }

    // Now the actual matching
    int n = haystack_size;
    assert(n >= 0);
    int seen = 0;
    for (int i = 0; i < n; ++i){
      while (seen > 0 and haystack[i] != needle[seen]) {
        seen = border[seen - 1];
      }
      if (haystack[i] == needle[seen]) seen++;

      if (seen == m) {
        // printf("Needle occurs from %d to %d\n", i - m + 1, i);
        return i;
        seen = border[m - 1];
      }
    }
    return -1;
  }

  string solve(const string& text, string& pattern) {
    vector<string> tokens;

    for (int i = 0; i < pattern.size(); ++i) {
      if (pattern[i] == '*') {
        pattern[i] = ' ';
      }
    }
    stringstream sin(pattern);

    // string t = "";
    // for (int i = 0; i <= pattern.size(); ++i) {
    //   if (i >= pattern.size() || pattern[i] == '*') {
    //     if (t.size() > 0) {
    //       tokens.push_back(t);
    //     }
    //     t = "";
    //   } else {
    //     t += pattern[i];
    //   }
    // }
    // if (tokens.size() == 0) return "yes";

    int from = 0;
    for (string token; sin >> token; ) {
      int end = kmp(token, text.c_str() + from, text.size() - from);
      if (end == -1) return "no";
      from = from + end + 1;
    }

    return "yes";
  }


  int main(){
    int n;
    while (cin >> n) {
      string text;
      assert(cin >> text);
      while (n--) {
        string pattern;
        assert(cin >> pattern);
        cout << solve(text, pattern) << endl;
      }
    }
    return 0;
  }
