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

const long long MAXN = 1000000000000005LL;
const int MAXK = 300005;
const int MAXR = 31622778;

vector<long long> places;

long long getRing(long long n) {
    if (n == 1) return 0;
    long long low = 0, high = MAXR;
    while (low < high) {
        long long m = (low + high) / 2;
        long long end = (2*m + 1) * (2*m + 1);
        if (end >= n) {
            high = m;
        } else {
            low = m + 1;
        }
    }
    return low;
}

long long getPrevious(long long b) {
    assert(b >= 4);
    long long r = getRing(b);
    assert(r > 0);
    long long first = (2*r - 1) * (2*r - 1) + 1;
    long long length = (2*r + 1) * (2*r + 1) - first + 1;
    assert(length % 4 == 0);
    int part = (b - first) / (length / 4);
    assert(part < 4);
    long long diff = 8 * r - 7 + 2 * part;
    return b - diff;
}

vector< pair<int, long long> > g[MAXK];

void dijkstra(int start, int end) {
    static long long dist[MAXK];
    const long long oo = 1000000000000000000LL;
    int n = places.size();
    for (int i = 0; i < n; ++i) {
        dist[i] = oo;
        assert(g[i].size() > 0);
        assert(g[i].size() <= 4);
    }
    dist[start] = 0;
    priority_queue< pair<long long, int>, vector<pair<long long, int> >, greater< pair<long long, int> > > q;
    q.push( make_pair(0, start) );
    while (q.size() > 0) {
        long long w = q.top().first;
        int u = q.top().second;
        q.pop();
        if (u == end) {
            cout << w << endl;
            return;
        }
        
        if (dist[u] < w) continue;
        foreach(out, g[u]) {
            long long w_extra = out->second;
            int v = out->first;
            if (w + w_extra < dist[v]) {
                dist[v] = w + w_extra;
                q.push( make_pair(dist[v], v) );
            }
        }
    }
    
}

int main(){
    ios::sync_with_stdio(false);

    places.push_back(1);
    int k;
    long long n;
    cin >> n >> k;
    places.push_back(n);
    vector<long long> doors;
    for (int i = 0; i < k; ++i) {
        long long b; cin >> b;
        places.push_back(b);
        long long a = getPrevious(b);
        places.push_back(a);

        doors.push_back(b);
    }
    sort(places.begin(), places.end());
    places.resize(unique(places.begin(), places.end()) - places.begin());
    assert(places[0] == 1);
    assert(places.size() < MAXK);
    
    for (int i = 0; i < doors.size(); ++i) {
        long long b = doors[i];
        long long a = getPrevious(b);
        
        int ia = lower_bound(places.begin(), places.end(), a) - places.begin();
        int ib = lower_bound(places.begin(), places.end(), b) - places.begin();
        g[ia].push_back(make_pair(ib, 1LL));
        g[ib].push_back(make_pair(ia, 1LL));
    }
    
    for (int i = 1; i < places.size(); ++i) {
        long long w = places[i] - places[i - 1];
        g[i - 1].push_back(make_pair(i, w));
        g[i].push_back(make_pair(i - 1, w));
    }
    
    dijkstra(0, lower_bound(places.begin(), places.end(), n) - places.begin());
    return 0;
}