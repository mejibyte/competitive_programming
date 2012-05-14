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

const int MAXN = 2 * 100005;
int a[MAXN], b[MAXN], id[MAXN];

int main(){
    ios::sync_with_stdio(false);
    
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];    
    for (int i = 0; i < n; ++i) id[b[i]] = i;
    for (int i = 0; i < n; ++i) a[i] = id[a[i]];
    
    int ans = 0, biggest = -1;
    for (int i = 0; i < n; ++i) {
        if (biggest > a[i]) {
            ans = n - i;
            break;
        }
        biggest = max(biggest, a[i]);
    }
    
    cout << ans << endl;
    return 0;
}