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

double memo[MAXN][60];
int status[MAXN][60];
int finish;

enum { White, Gray, Black };

int waitTime(int t1, int t2) {
    return ((t2 - t1) + 60) % 60;
}

double E(int u, int t) {
    if (u == finish) return 0.0;
    if (status[u][t] == Black) return memo[u][t];
    if (status[u][t] == Gray) return 1e50;
    
    double ans = 1e99;
    status[u][t] = Gray;
    for (int k = 0; k < outgoing[u].size(); ++k) {
        const Train &train = outgoing[u][k];
        
        double option = waitTime(t, train.departure) + train.duration;
        if (status[train.to][(train.departure + train.duration) % 60] == Gray) continue;
        double e = E(train.to, (train.departure + train.duration) % 60);
        option += (1.0 - train.probability) * e;
        
        bool good = true;
        double delayProbability = train.probability / train.delay;
        for (int d = 1; d <= train.delay; ++d) {
            if (status[train.to][(train.departure + train.duration + d) % 60] == Gray) {
                good = false;
                break;
            }
            double e = E(train.to, (train.departure + train.duration + d) % 60);
            option += delayProbability * (d + e);
        }
        
        if (good) ans = min(ans, option);
    }
    status[u][t] = Black;
    memo[u][t] = ans;
    return ans;
}

void solve() {
    id.clear();
    int nextId = 0;
    string start, end;
    cin >> start >> end;
    assert(start != end);
    id[start] = nextId++;
    finish = id[end] = nextId++;
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
    
    memset(status, 0, sizeof status);

    double ans = 1e100;
    for (int t = 0; t < 60; ++t) {
        ans = min(ans, E(id[start], t));
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