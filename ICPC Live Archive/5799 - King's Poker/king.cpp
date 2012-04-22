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

int a, b, c;

void solve() {
    if (a == 13 and b == 13 and c == 13) {
        puts("*");
        return;
    }

    if (a == b and b == c) { // triplet
        printf("%d %d %d\n", a + 1, a + 1, a + 1);
        return;
    }
    
    if (a == b or b == c or a == c) { // pair
        if (a == b) swap(a, c); // free is c
        else if (a == c) swap(a, b); // free is b
        assert(b == c and a != b and a != c);
        
        if (a == 12 and b == 13) { // last pair
            puts("1 1 1");
            return;
        }

        int ans[3] = { a, b, c };
        
        ans[0]++;
        if (ans[0] == ans[1]) ans[0]++;
        if (ans[0] > 13) { // next pair
            ans[0] = 1, ans[1]++, ans[2]++;
        }
        sort(ans, ans + 3);
        printf("%d %d %d\n", ans[0], ans[1], ans[2]);
        return;
    }
    puts("1 1 2");
}

int main(){
    while (cin >> a >> b >> c) {
        if (a == 0 and b == 0 and c == 0) break;
        solve();
    }
    return 0;
}