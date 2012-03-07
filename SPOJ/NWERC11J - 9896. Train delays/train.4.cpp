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

const int MAXN = 2005;

struct Train {
    int from, to, departure, duration, delay;
    double probability;
};

vector< Train > incoming[MAXN];
map< string, int > id;

double E[MAXN][60];
int start, finish;

int waitTime(int t1, int t2) {
    return ((t2 - t1) + 60) % 60;
}

double expectedTrip(int u, int t, const Train &train) {
    assert(train.from == u);
    double ans = waitTime(t, train.departure) + train.duration;
    double e = E[train.to][(train.departure + train.duration) % 60];
    if (e > 1e99) return 1e100;
    ans += (1.0 - train.probability) * e;

    double delayProbability = train.probability / train.delay;
    for (int d = 1; d <= train.delay; ++d) {
        double e = E[train.to][(train.departure + train.duration + d) % 60];
        if (e > 1e99) return 1e100;
        ans += delayProbability * (d + e);
    }
    return ans;
}

void solve() {
    id.clear();
    int nextId = 0;
    string startStr, finishStr;
    cin >> startStr >> finishStr;
    assert(startStr != finishStr);
    start = id[startStr] = nextId++;
    finish = id[finishStr] = nextId++;
    int trainCount; cin >> trainCount;
    for (int i = 0; i < trainCount; ++i) {
        string from, to; int m, t, p, d;
        cin >> from >> to >> m >> t >> p >> d;
        Train train;
        train.to = id.count(to) ? id[to] : (id[to] = nextId++);
        train.from = id.count(from) ? id[from] : (id[from] = nextId++);
        train.departure = m;
        train.duration = t;
        train.probability = p / 100.0;
        train.delay = d;

        incoming[train.to].push_back(train);
    }
    
    int n = nextId;
    for (int t = 0; t < 60; ++t) {
        for (int i = 0; i < n; ++i) {
            E[i][t] = 1e100;
        }
        E[finish][t] = 0.0;
    }

    priority_queue< pair<double, pair<int, int> > > q;
    q.push( make_pair(0.0, make_pair(finish, 0)) );
    while (q.size() > 0) {
        double w = -q.top().first;
        int v = q.top().second.first;
        int arrivalTime = q.top().second.second;
        q.pop();
        if (cmp(w, E[v][arrivalTime]) > 0) continue;
        
        for (int k = 0; k < incoming[v].size(); ++k) {
            const Train &train = incoming[v][k];
            assert(train.to == v);
            int u = train.from;
            int t = train.departure;
            double e = expectedTrip(u, t, train);
            if (cmp(e, E[u][t]) < 0) {
                E[u][t] = e;
                q.push(  make_pair(-e, make_pair(u, t)) );
                
                // Now stay at the station
                for (int minute = 0; minute < 60; ++minute) {
                    int wait = waitTime(minute, t);
                    if (cmp(wait + E[u][t], E[u][minute]) < 0) {
                        E[u][minute] = wait + E[u][t];
                    }
                }
            }
        }
    }
    
    double ans = 1e100;
    for (int t = 0; t < 60; ++t) {
        ans = min(ans, E[start][t]);
    }
    if (ans < 10e20) {
        printf("%.10lf\n", ans);
    } else {
        printf("IMPOSSIBLE\n");
    }
    
    for (int i = 0; i < nextId; ++i) {
        incoming[i].clear();
    }
}

int main(){
    int T; cin >> T; while (T--) {
        solve();
    }
    return 0;
}