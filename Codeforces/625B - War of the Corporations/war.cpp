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

// KMP prefix array.
vector<int> p;
void compute_kmp(const string &s) {
    int m = s.size();
    p.resize(m);
    p[0] = 0;
    for (int i = 1; i < m; ++i) {
      p[i] = p[i - 1];
      while (p[i] > 0 && s[i] != s[p[i]]) {
        p[i] = p[p[i] - 1];
      }
      if (s[i] == s[p[i]]) {
        p[i]++;
      }
    }
}

// Returns all occurrences of pattern in text.
//
// Each occurrence is represented as the rightmost index of the match in text.
//
// Example:
//    match("ababacaba", "aba") => {2, 4, 8}
vector<int> match(const string &text, const string &pattern) {
  vector<int> matches;
  int seen = 0;
  for (int i = 0; i < text.size(); ++i) {
    while (seen > 0 && text[i] != pattern.at(seen)) {
      seen = p[seen - 1];
    }
    if (text[i] == pattern[seen]) {
      seen++;
      if (seen >= pattern.size()) {
        matches.push_back(i);
        seen = p[seen - 1];
      }
    }
  }
  return matches;
}


int main(){
    string text, pattern;
    cin >> text >> pattern;

    // KMP is overkill for this problem but I did it for practice.
    compute_kmp(pattern);

    vector<int> matches = match(text, pattern);

    int answer = 0;
    int last_changed_character = -1;
    for (int i = 0; i < matches.size(); ++i) {
      int end = matches[i];
      int begin = end - pattern.size() + 1;
      if (last_changed_character < begin) {
        // Choose this one.
        answer++;
        last_changed_character = end;
      }
    }
    cout << answer << endl;
    return 0;
}
