// This is too slow.

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

vector<int> a, b;

bool read() {
    int n = 10;
    a.resize(n);
    b.resize(n);
    for (int i = 0; i < n; ++i) {
        if (!(cin >> a[i])) return false;
        a[i]--;
    }
    for (int i = 0; i < n; ++i) {
        if (!(cin >> b[i])) return false;
        b[i]--;
    }
    return true;
}

long long encode(const vector<int> &v) {
    long long ans = 0;
    for (int i = 9; i >= 0; --i) ans = 10*ans + v[i];
    return ans;
}

void decode(long long x, vector<int> &v) {
    v.resize(10);
    for (int i = 0; i < 10; ++i) v[i] = x % 10, x /= 10;
}

int main(){
    
    while (read()) {
        map< long long, int > dist;
        queue< long long > q;
        dist[encode(a)] = 0;        
        q.push( encode(a) );
        
        int n = 10;
        while (q.size() > 0) {
            D(dist.size());
            
            vector<int> u;
            decode(q.front(), u);
            q.pop();

            if (encode(u) == encode(b)) break;

            int here = dist[encode(u)];
            
            for (int i = 0; i < n; ++i) {
                for (int j = i + 1; j < n; ++j) {
                    reverse(u.begin() + i, u.begin() + j + 1);
                    long long v = encode(u);
                    if (dist.count(v) == 0) {
                        dist[v] = here + 1;
                        q.push(v);
                    }
                    reverse(u.begin() + i, u.begin() + j + 1);                    
                }
            }
        }
        cout << dist[encode(b)] << endl;
    }
    return 0;
}