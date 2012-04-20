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

int power[10];

#include <bitset>
const int MAXN = 2000005;
bitset<2000005> seen;

void solve() {
    int a, b;
    cin >> a >> b;
    
    int n = 0;
    for (int x = b; x > 0; x /= 10) n++;
    
    
    int ans = 0;
    for (int i = a; i <= b; ++i) {
        for (int k = 1; power[k] <= b; ++k) {
            int j = (i % power[k]) * power[n - k] + i / power[k];
            if (a <= i and i <= b and a <= j and j <= b and i < j) {
                if (!seen[j]) {
                    ans++;
                }
                seen[j] = true;
            }
        }
        

        for (int k = 1; power[k] <= b; ++k) {
            int j = (i % power[k]) * power[n - k] + i / power[k];
            if (j < MAXN) seen[j] = false;
        }
    }
    cout << ans << endl;
}

int main(){
    power[0] = 1;
    for (int i = 1; i < 10; ++i) power[i] = power[i - 1] * 10;
    
    int runs; cin >> runs;
    for (int i = 1; i <= runs; ++i) printf("Case #%d: ", i), solve();
    return 0;
}