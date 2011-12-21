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

// This will certainly time out, but get off my lawn.

#define SIZE(t) ((int)((t).size()))

// the original tree
int N;
vector<vector<int> > G; 

vector<unsigned int> salary;

void shoot(int u, int delta) {
    for (int k = 0; k < G[u].size(); ++k) {
        int v = G[u][k];
        salary[v] += delta;
        shoot(v, delta);
    }
}

int main(){
    int Q;
    cin >> N >> Q;
    G.clear(); G.resize(N);
    salary.resize(N);
    cin >> salary[0];
    
    for (int i=1; i<N; ++i) {
        int p;
        cin >> salary[i] >> p;
        p--;
        G[p].push_back(i);
    }
    
    for (int q = 0; q < Q; ++q) {
        char type; scanf(" %c ", &type);
        if (type == 'p') { // increase
            int u, delta;
            scanf("%d %d", &u, &delta);
            u--;
            shoot(u, delta);
        } else { // how much?
            int u; scanf("%d", &u);
            u--;
            printf("%d\n", salary[u]);
        }
    }
    
    return 0;
}
