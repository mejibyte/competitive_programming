// Andrés Mejía
using namespace std;
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

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

bool permute(vector<int> &p) {
    int n = p.size();
    for (int i = n - 2; i >= 0; --i) {
        if (p[i] < p[i + 1]) {
            int best = i + 1;
            for (int j = i + 2; j < n; ++j) if (p[j] > p[i] and p[j] < p[best]) best = j;
            swap(p[i], p[best]);
            reverse(p.begin() + i + 1, p.end());
            return true;
        }
    }
    return false;
}

int main(){
    int n; cin >> n;
    vector<int> p(n);
    int ans = 1;
    for (int i = 0; i < n; ++i) {
        p[i] = i + 1;
        ans *= i + 1;
    }
    cout << ans << endl;
    do {
        for (int i = 0; i < n; ++i) cout << p[i] << " "; cout << endl;
    } while (permute(p));
    return 0;
}