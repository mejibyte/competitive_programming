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

int a[20], b[20];

int main(){
    for (int i = 0; i < 20; ++i) {
        cin >> a[i];
        b[i] = a[i];
    }

    int ans = INT_MAX, score;
    
  // do not flip first one
    score = 0;
    for (int i = 1; i < 20; ++i) {
        if (a[i - 1] == 1) {
            a[i - 1] ^= 1, a[i] ^= 1, a[i + 1] ^= 1;
            score++;
        }
    }
    if (*max_element(a, a + 20) == 0) ans = min(ans, score);
    
    for (int i = 0; i < 20; ++i) a[i] = b[i];
  
    // flip first one
    score = 1;
    a[0] ^= 1, a[1] ^= 1;
    for (int i = 1; i < 20; ++i) {
        if (a[i - 1] == 1) {
            a[i - 1] ^= 1, a[i] ^= 1, a[i + 1] ^= 1;
            score++;
        }
    }
    if (*max_element(a, a + 20) == 0) ans = min(ans, score);
  
    cout << ans << endl;
    
    return 0;
}