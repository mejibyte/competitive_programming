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


// Brute force - TLE
vector<int> a;
int n;
vector<bool> taken;

bool search(int stick_size, int need, int used) {
  if (used >= n) return need == 0;
  if (need == 0) return search(stick_size, stick_size, used);
  for (int i = 0; i < n; ++i) {
    if (taken[i]) continue;

    if (i - 1 >= 0 and a[i] == a[i - 1] and !taken[i - 1]) continue;

    if (a[i] > need) continue;

    taken[i] = true;
    if (search(stick_size, need - a[i], used + 1)){
      return true;
    }
    taken[i] = false;
  }

  return false;
}

int main(){
  // ios::sync_with_stdio(0);
  // cin.tie(0);
  while (cin >> n) {
    if (n == 0) break;
    a.resize(n);
    taken.assign(n, false);
    int sum = 0;
    int largest_piece = 0;
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
      sum += a[i];
      largest_piece = max(largest_piece, a[i]);
    }
    assert(n <= 64);
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    int answer = sum;
    for (int d = largest_piece; d < sum; d++) {
      if (sum % d != 0) continue;
      if (search(d, d, 0)) {
        answer = d;
        break;
      }
    }
    cout << answer << endl;
  }
  return 0;
}