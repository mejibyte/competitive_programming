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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);

    set<pair<int, int>> s;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] > 0) {
            s.insert( make_pair(a[i], i+1) );
        }
    }

    vector<pair<int, int>> answer;
    while (s.size() >= 2) {
        pair<int, int> low = *s.begin();
        pair<int, int> high = *--s.end();

        assert(low.first > 0 and high.first > 0);
        s.erase(low);
        s.erase(high);
        low.first--;
        high.first--;
        answer.push_back(make_pair(low.second, high.second));
        if (low.first > 0) s.insert(low);
        if (high.first > 0) s.insert(high);
    }

    cout << answer.size() << endl;
    for (int i = 0; i < answer.size(); ++i) {
        cout << answer[i].first << " " << answer[i].second << endl;
    }
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
