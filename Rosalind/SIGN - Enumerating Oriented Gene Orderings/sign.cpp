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


int main(){
    int n; cin >> n;
    vector<int> p(n);
    int ans = 1;
    for (int i = 0; i < n; ++i) {
        p[i] = i + 1;
        ans *= i + 1;
    }
    ans <<= n;
    cout << ans << endl;
    do {
        for (int mask = 0; mask < 1 << n; ++mask) {
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) cout << "-";
                cout << p[i] << " ";
            }
            cout << endl;
        }
    } while (next_permutation(p.begin(), p.end()));
    return 0;
}