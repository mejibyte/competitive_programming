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

int extra(long long p1, long long p2, long long a) {
    long long p = min(p1, p2);
    p = ((p % a) + a) % a;
    long long k = abs(p1 - p2) % a;
    return p + k >= a;
}

int main(){
    long long a, b, x1, y1, x2, y2;
    cin >> a >> b >> x1 >> y1 >> x2 >> y2;
    
    long long p1, q1, p2, q2;
    p1 = x1 + y1, q1 = x1 - y1;
    p2 = x2 + y2, q2 = x2 - y2;
    

    a *= 2, b *= 2;

    long long ans = max( (abs(p1 - p2) / a) + extra(p1, p2, a),
                         (abs(q1 - q2) / b) + extra(q1, q2, b) );
    
    cout << ans << endl;
    return 0;
}