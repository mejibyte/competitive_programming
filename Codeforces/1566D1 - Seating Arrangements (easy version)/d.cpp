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
  FenwickTree(int _maxSize) : maxSize(_maxSize+1) {
    v = vector<long long>(maxSize + 10, 0LL);
  }

  void add(int where, long long what){
    for (where++; where <= maxSize; where += where & -where){
      v.at(where) += what;
    }
  }

  long long query(int where){
    long long sum = v.at(0);
    for (where++; where > 0; where -= where & -where){
      sum += v.at(where);
    }
    return sum;
  }

  long long query(int from, int to){
    return query(to) - query(from-1);
  }

};

struct Person {
    int vision, index;
};

bool operator < (const Person& a, const Person &b) {
    if (a.vision != b.vision) {
        return a.vision < b.vision;
    }
    return a.index > b.index;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<Person> p(m);
    for (int i = 0; i < m; ++i) {
        cin >> p[i].vision;
        p[i].index = i;
    }
    sort(p.begin(), p.end());

    vector<int> seat(m + 10);
    for (int i = 0; i < p.size(); ++i) {
        seat[p[i].index] = i;
    }

    FenwickTree tree(m + 10);

    long long ans = 0;
    for (int i = 0; i < m; i++) {
        int my_seat = seat[i];

        if (my_seat > 0) ans += tree.query(my_seat - 1);
        tree.add(my_seat, +1);
    }
    cout << ans << endl;

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
