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


class FenwickTree{
  vector<long long> v;
  int maxSize;

public:
  FenwickTree(int _maxSize) : maxSize(_maxSize+10) {
    v = vector<long long>(maxSize+10, 0LL);
  }

  void add(int where, long long what){
    for (where++; where <= maxSize; where += where & -where){
      v[where] += what;
    }
  }

  long long query(int where){
    long long sum = v[0];
    for (where++; where > 0; where -= where & -where){
      sum += v[where];
    }
    return sum;
  }

  long long query(int from, int to){
    if (from > to) return 0;
    return query(to) - query(from-1);
  }

};



void solve() {
    int n;
    cin >> n;
    long long answer = 0;

    vector<int> a(n);
    vector<int> sorted(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sorted[i] = a[i];
    }
    sort(sorted.begin(), sorted.end());
    sorted.resize(unique(sorted.begin(), sorted.end()) - sorted.begin());
    for (int i = 0; i < n; ++i) {
        a[i] = lower_bound(sorted.begin(), sorted.end(), a[i]) - sorted.begin();
    }


    FenwickTree tree(n+10);
    for (int i = 0; i < n; ++i) {
        long long option1 = tree.query(0, a[i] - 1);
        long long option2 = tree.query(a[i] + 1, n);

        answer += min(option1, option2);

        tree.add(a[i], 1);
    }
    cout << answer << endl;

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
