// Andrés Mejía

// Accepted

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
const int MAXS = 1005;
const int MAXN = 10005;

typedef pair<int, int> point;

vector <pair <int, int> > p;
int w, h;

typedef pair< double, int > queueItem;

int read() {
    int a, b;
    scanf("%d.%d", &a, &b);
    return a * 100 + b;
}

double dist(const point &a, const point &b) {
    int dx = a.first - b.first;
    int dy = a.second - b.second;
    return sqrt(dx * dx + dy * dy);
}

double dijkstra() {
    static double d[MAXN];
    for (int i = 0; i < MAXN; ++i) {
        d[i] = 1e100;
    }
    assert(p[0] == make_pair(0, 0));
    d[0] = 0.0;
    priority_queue< queueItem, vector<queueItem>, greater<queueItem> > q;
    q.push( make_pair(0.0, 0) );
    
    while (q.size() > 0) {
        int cur = q.top().second;
        double w = q.top().first;
        q.pop();
        
        //printf("popped (%d, %d) with %lf\n", p[cur].first, p[cur].second, w);

        if (cur == p.size() - 1) return w;
        if (cmp(w, d[cur]) > 0) continue;
        
        int from = cur;
        while (from >= 0 and p[cur].first - p[from].first <= 150) from--;
        int to = cur;
        while (to < p.size() and p[to].first - p[cur].first <= 150) to++;
        
        for (int i = from + 1; i < to; ++i) {
            if (i == cur) continue;
            double w_extra = dist(p[cur], p[i]);
            if (cmp(w_extra, 150) <= 0) {
                if (cmp(w + w_extra, d[i]) < 0) {
                    d[i] = w + w_extra;
                    q.push( make_pair(d[i], i) );
                }
            }
        }
    }
    return 1e100;
}


int main(){
    while (scanf("%d %d", &w, &h) == 2){
        int n; scanf("%d", &n);
        
        p.clear();
        for (int i = 0; i < n; i++){
            int x, y;
            x = read(), y = read();
            if (x == 0 and y == 0 or x == 100*w and y == 100*h)  continue;
            p.push_back(make_pair(x, y));
        }
        p.push_back(make_pair(0, 0));
        p.push_back(make_pair(100 * w, 100 * h));
        sort(p.begin(), p.end());

        assert(p.back() == make_pair(100 * w, 100 * h));
        int minDistance = read();
        
        double ans = dijkstra();
        if (cmp(ans, minDistance) <= 0) {
            puts("I am lucky!");
        }else{
            puts("Boom!");
        }
    }
    return 0;
}