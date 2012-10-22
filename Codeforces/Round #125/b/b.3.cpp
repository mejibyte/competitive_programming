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

struct State {
    int p, h, t;
    State(int pp, int hh, int tt) : p(pp), h(hh), t(tt) {}

    bool operator < (const State &other) const {
        return t > other.t;
    }
};

int best[2][100005];

queue<State> q;

void enqueue(int p, int h, int new_t) {
    if (new_t < best[p][h]) {
        best[p][h] = new_t;
        q.push(State(p, h, new_t));
    }
}

int main(){
    int n, k; cin >> n >> k;
    string w[2]; cin >> w[0] >> w[1];
    w[0] = " " + w[0];
    w[1] = " " + w[1];
    
    for (int i = 0; i <= n; ++i) best[0][i] = best[1][i] = 1 << 30;
    best[0][1] = 0;
    

    State start = State(0, 1, 0);
    q.push(start);
    bool reached = false;
    
    while (q.size() > 0) {
        int h = q.front().h;
        int p = q.front().p;
        int t = q.front().t;
        q.pop();
        if (t > best[p][h]) continue;
        
        if (h + k > n) { // jump out
            reached = true;
            break;
        }

        if (w[p ^ 1][h + k] == '-') {
            enqueue(p ^ 1, h + k, t + 1);
        }
        
        if (w[p][h + 1] == '-') {
            enqueue(p, h + 1, t + 1);
        }
        
        if (h - 1 > t + 1 and h - 1 >= 1 and w[p][h - 1] == '-') {
            enqueue(p, h - 1, t + 1);
        }
    }
    
    cout << (reached ? "YES" : "NO") << endl;

    return 0;
}