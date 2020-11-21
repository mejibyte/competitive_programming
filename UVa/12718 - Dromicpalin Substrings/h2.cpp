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
#include <unordered_set>
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

void solve(const string &s) {
  int n = s.size();
  int answer = 0;
  for (int i = 0; i < n; ++i) {
    vector<bool> even(256, true);
    int odd = 0;
    for (int j = i; j < n; ++j) {
      char c = s[j];
      if (even[c]) {
        even[c] = false;
        odd++;
      } else {
        even[c] = true;
        odd--;
      }
      assert(odd >= 0);
      answer += (odd <= 1);
    }

  }
  printf("%d\n", answer);
}

int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);

  int C;
  cin >> C;
  for (int c = 1; c <= C; ++c) {
    string s;
    cin >> s;
    printf("Case %d: ", c);
    solve(s);
  }
    return 0;
}