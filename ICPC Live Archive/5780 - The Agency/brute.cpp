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

int tax[1005];

int cost(const string &s) {
    int ans = 0;
    for (int i = 0; i < s.size(); ++i) if (s[i] == '1') ans += tax[i];
    return ans;
}

void solve(int n) {
    string start, end; cin >> start >> end;
    for (int i = 0; i < n; ++i) cin >> tax[i];
    
    priority_queue<pair<int, string>, vector<pair<int, string> >, greater<pair<int, string> > > q;
    map<string, int> d;
    map<string, string> from;
    
    q.push(make_pair(0, start));
    d[start] = 0;
    while (q.size() > 0) {
        int w = q.top().first;
        string s = q.top().second;
        q.pop();
        
        if (d[s] < w) continue;
        if (s == end) {
            printf("%d\n", w);
            
            vector<string> ans;
            while (from.count(s)) {
                ans.push_back(s);
                s = from[s];
            }
            ans.push_back(s);
            
            //for (int i = ans.size() - 1; i >= 0; --i) puts(ans[i].c_str());

            return;
        }
        
        for (int k = 0; k < n; ++k) {
            string t = s;
            t[k] = s[k] == '1' ? '0' : '1';
            if (d.count(t) == 0 or w + cost(t) < d[t]) {
                d[t] = w + cost(t);
                q.push(make_pair(d[t], t));
                from[t] = s;
            }
        }
    }
}

int main(){
    int run = 1, n;
    while (cin >> n and n > 0) {
        printf("Case %d: ", run++);
        solve(n);
    }
    return 0;
}