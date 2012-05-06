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

const int MAXN = 105;

int n;
int a[MAXN];
int b[MAXN];

bool can[MAXN][MAXN];
bool visited[MAXN];

vector<int> indices, values;

void shoot(int u){
    if (visited[u]) return;
    visited[u] = true;
    indices.push_back(u);
    values.push_back(a[u]);
    for (int v = 0; v < n; ++v) {
        if (u != v and can[u][v]) shoot(v);
    }
}

int main(){
    cin >> n;
    
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        b[i] = a[i];
    }
    
    memset(can, false, sizeof can);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char c; cin >> c;
            can[i][j] = (c == 'Y');
        }
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            can[i][j] = (can[i][j] or can[j][i]);
        }
    }
    
    memset(visited, false, sizeof visited);
    for (int i = 0; i < n; ++i){
        if (!visited[i]) {
            indices.clear(), values.clear();
            shoot(i);
            sort(indices.begin(), indices.end());
            sort(values.begin(), values.end());
            assert(indices.size() == values.size());
            for (int k = 0; k < indices.size(); ++k) {
                int where = indices[k];
                int what = values[k];
                b[where] = what;
            }
        }
    }
    
    for (int i = 0; i < n; ++i){
        if (i > 0) cout << " ";
        cout << b[i];
    }
    cout << endl;
    
    return 0;
}