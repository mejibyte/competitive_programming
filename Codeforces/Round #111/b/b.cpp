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
    string s; cin >> s;
    sort(s.begin(), s.begin() + n);
    sort(s.begin() + n, s.end());
    bool ok1 = true;
    for (int i = 0; i < n; ++i) ok1 &= s[i] < s[i + n];
    bool ok2 = true;
    for (int i = 0; i < n; ++i) ok2 &= s[i] > s[i + n];
    cout << (ok1 || ok2 ? "YES" : "NO") << endl;
    return 0;
}