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

vector< set<int> > cubes;

bool can_make(int k) {
  vector<int> digits;
  while (k > 0) {
    digits.push_back(k % 10);
    k /= 10;
  }

  sort(cubes.begin(), cubes.end());
  do {
    bool works = true;
    for (int i = 0; i < digits.size() && works; ++i) {
      if (i >= cubes.size() or cubes[i].count(digits[i]) == 0) {
        works = false;
      }
    }
    if (works) return true;
  } while (next_permutation(cubes.begin(), cubes.end()));

  return false;
}

int main(){
  int n;
  cin >> n;
  cubes.resize(n);
  for (int i = 0; i < n; ++i) {
    cubes[i].clear();
    for (int k = 0; k < 6; ++k) {
      int face;
      cin >> face;
      cubes[i].insert(face);
    }
  }
  int ans = 0;
  for (int i = 1; can_make(i); ++i) {
    ans = i;
  }
  cout << ans << endl;
  return 0;
}
