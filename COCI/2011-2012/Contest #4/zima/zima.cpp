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

const int MAXN = 100005;

int a[MAXN];
vector<bool> announce;

int main(){
    ios::sync_with_stdio(false);
    
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    announce.assign(n, false);
    
    vector< pair<int, int> > winters; // first = length, second = first day
    
    for (int i = 0; i < n; i++) {
        if (a[i] >= 0) continue;
        
        int j = i;
        while (j < n and a[j] < 0) j++;
        int len = j - i;
        winters.push_back( make_pair(len, i) );
        
        for (int back = 1; back <= 2*len; ++back) {
            if (i - back < 0) break;
            announce[i - back] = true;
        }
        i = j - 1;
    }
    if (winters.size() == 0) {
        cout << 0 << endl;
        return 0;
    }
    
    sort(winters.begin(), winters.end(), greater< pair<int, int> >());
    
    int W = 0;
    while (W < winters.size() and winters[W].first == winters[0].first) W++;
    winters.resize(W);
    // now winters has the longest winters. Brute force each to find the maximum
    
    int extra = 0;
    foreach(w, winters) {
        int i = w->second;
        int len = w->first;
        int adds = 0;
        for (int back = 1; back <= 3*len; ++back) {
            if (i - back < 0) break;
            if (!announce[i - back]) adds++;
        }
        extra = max(adds, extra);
    }
    
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += announce[i];
    }
    ans += extra;
    cout << ans << endl;
    return 0;
}