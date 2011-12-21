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

int main(){
    int a, b, x1, y1, x2, y2;
    cin >> a >> b >> x1 >> y1 >> x2 >> y2;
    
    int p1, q1, p2, q2;
    p1 = x1 + y1, q1 = x1 - y1;
    p2 = x2 + y2, q2 = x2 - y2;

    a *= 2, b *= 2;
    
    p1 = p1 / a - (p1 < 0);
    p2 = p2 / a - (p2 < 0);
    q1 = q1 / b - (q1 < 0);
    q2 = q2 / b - (q2 < 0);
    
    int ans = max( abs(p1 - p2),  abs(q1 - q2) );
    cout << ans << endl;
    return 0;
}