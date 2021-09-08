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

void solve(const string &s) {
    for (int i = 0; i < s.size(); ++i) {
        int a = 0, b = 0;
        for (int j = i; j < s.size(); ++j) {
            if (s[j] == 'a') a++;
            if (s[j] == 'b') b++;
            if (a == b) {
                cout << i+1 << " " << j+1 << endl;
                return;
            }
        }
    }
    cout << "-1 -1" << endl;
}

int main(){
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        solve(s);
    }
    return 0;
}
