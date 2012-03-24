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
const int MAXN = 10S005;

vector <pair <double,double> > p;
vector <pair <int, double > > g [MAXN];

int main(){
    int w, h;
    while (scanf("%d %d", &w, &h) == 2){
        int n; cin >> n;
        for (int i = 0; i < n; i++){
            double x, y;
            cin >> x >> y;
            p.push_back(make_pair(x, y));
        }
        sort(p.begin(), p.end());
        for (int curr = 0; curr < n; curr++){
            for (int next = curr + 1; next < n; next++){
                int d = dist(curr, next);
                if (d > 1.5) break;
                g[curr].push_back(make_pair(next, d));
                g[next].push_back()
            }
        }
    }
    return 0;
}