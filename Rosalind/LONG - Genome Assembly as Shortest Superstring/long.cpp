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

int overlap(const string &s, const string &t) {
    for (int len = min(s.size(), t.size()); len >= 0; --len) {
        if (s.substr(s.size() - len) == t.substr(0, len)) return len;
    }
    assert(false);
}

int main(){
    vector<string> v;
    for (string s; cin >> s; v.push_back(s));
    string ans = v[0];
    int n = ans.size();
    vector<bool> used(n, false);
    used[0] = true;
    
    
    for (int k = 1; k < v.size(); ++k) {
        for (int i = 0; i < v.size(); ++i) {
            if (used[i]) continue;
            
            int length = overlap(ans, v[i]);
            if (2 * length > n) {
                ans = ans + v[i].substr(length);
                used[i] = true;
                break;
            }
            
            length = overlap(v[i], ans);
            if (2 * length > n) {
                ans = v[i] + ans.substr(length);
                used[i] = true;
                break;
            }
        }
    }
    cout << ans << endl;
    return 0;
}