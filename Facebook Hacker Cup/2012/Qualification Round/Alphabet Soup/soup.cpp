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

int count(string s) {
    map< char, int > times;
    for (int k = 0; k < s.size(); ++k) times[s[k]]++;
    
    string slogan = "HACKERCUP";
    int ans = (1 << 30);
    for (int k = 0; k < slogan.size(); ++k) {
        ans = min(ans, times[ slogan[k] ]);
    }
    ans = min(ans, times['C'] / 2);
    return ans;
}

int main(){
    int T; cin >> T;
    string s; getline(cin, s);
    for (int i = 0; i < T; ++i) {
        getline(cin, s);
        printf("Case #%d: %d\n", i + 1, count(s));
    }
    return 0;
}