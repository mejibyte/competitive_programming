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
    int departure, duration, to, delay;
    double probability;
};

vector< Train > outgoing[MAXN];
map< string, int > id;

double E[MAXN][60];
int start, finish;

int waitTime(int t1, int t2) {
    return ((t2 - t1) + 60) % 60;
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
        train.departure = m;
        train.duration = t;
        train.probability = p / 100.0;
        train.delay = d;
        
        int u = id.count(from) ? id[from] : (id[from] = nextId++);
        outgoing[u].push_back(train);
    }
    
    int n = nextId;
    for (int t = 0; t < 60; ++t) {
        for (int i = 0; i < n; ++i) {
            E[i][t] = 1e100;
        }
        E[finish][t] = 0.0;
    }
    
    for (bool changed = true; changed; ) {
        changed = false;
        
        for (int u = 0; u < n; ++u) {
            for (int t = 0; t < 60; ++t) {
                for (int k = 0; k < outgoing[u].size(); ++k) {
                    const Train &train = outgoing[u][k];
                    double option = waitTime(t, train.departure) + train.duration;
                    double e = E[train.to][(train.departure + train.duration) % 60];
                    if (e > 1e99) continue;
                    option += (1.0 - train.probability) * e;

                    bool good = true;
                    double delayProbability = train.probability / train.delay;
                    for (int d = 1; d <= train.delay; ++d) {
                        double e = E[train.to][(train.departure + train.duration + d) % 60];
                        if (e > 1e99) {
                            good = false;
                            break;
                        }
                        option += delayProbability * (d + e);
                    }
                    if (good and cmp(option, E[u][t]) < 0) {
                        E[u][t] = option;
                        changed = true;
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
        outgoing[i].clear();
    }
}

int main(){
    int T; cin >> T; while (T--) {
        solve();
    }
    return 0;
}