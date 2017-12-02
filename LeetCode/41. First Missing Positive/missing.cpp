// Andrés Mejía
#include <unordered_map>
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

class Solution {
public:
    int firstMissingPositive(vector<int>& a) {
        int n = a.size();
        for (int i = 0; i < n; ++i) {
            a[i]--;
        }
        for (int i = 0; i < n; ++i) {
            while (0 <= a[i] and a[i] < n and a[a[i]] != a[i]) {
                swap(a[i], a[a[i]]);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (a[i] != i) return i + 1;
        }
        return n + 1;

    }
};

int main() {
  Solution s;
  vector<int> k;

  auto ans = s.firstMissingPositive(k = {1,1,2,1,1});
  D(ans);
  return 0;
}
