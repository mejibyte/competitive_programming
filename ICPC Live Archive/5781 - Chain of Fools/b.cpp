using namespace std;
#include <iostream>
#include <algorithm>
#include <iterator>
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
#include <map>
#include <set>
#include <stack>

#define D(x) cout << #x " = " << (x) << endl
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); x++)
#define For (i, a, b) for (int i = (a); i < (b); i++)

int S, C, a, b;

void solve() {
    int limit = S * C;
    assert(limit <= 20001);
    for (int t = 1; t <= limit; ++t) {
        
        int p = (a + t) % S;
        int q = (b + t) % C;
        
        if (p == 0 and q == 0) {
            printf("%d %d/%d\n", t / S, t % S, S);
            return;
        }
    }
    puts("Never");
}

int main (){
    int run = 1;
    while (cin >> S >> C >> a >> b) {
        if (S == 0 and C == 0 and a == 0 and b == 0) break;

        printf("Case %d: ", run++);
        solve();
    }

    return 0;
}
