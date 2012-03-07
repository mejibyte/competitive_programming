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

const int MAXN = 50005;
const int MAXS = 10000005;

vector< long long > ways[MAXS];
int need[MAXS + 1];

void solve() {
    int s; cin >> s;
    if (s == 1) { // special case
        puts("2");
        return;
    }
    
    int ans = s + 1;
    for (int i = 1; 1LL * i * i <= s; ++i) {
        if (s % i != 0) continue;
        
        int option = need[i] + need[s / i];
        if (option < ans) {
            // printf("better with i = %d (need = %d) and s / i = %d (need %d)\n", i, need[i], s / i, need[s / i]);
            ans = option;
        }
    }
    printf("%d\n", ans);
}

int main(){
    for (int i = 0; i < MAXS; ++i) {
        need[i] = i;
    }
    for (int i = 0; i < MAXN; ++i) {
        ways[0].push_back( 1 );
        ways[i].push_back( 1 );
    }
    for (int i = 1; i < MAXN; ++i) {
        for (int j = 1; j < MAXN; ++j) {
            if (j >= ways[i - 1].size()) break;
            long long w = 0LL + ways[i - 1][j] + ways[i][j - 1];
            if (w > MAXS) break;
            ways[i].push_back(w);
            if (i + j < need[w]) need[w] = i + j;
        }
        // printf("ways[i=%d] has %d elements\n", i, ways[i].size());
    }
    
    int runs; cin >> runs;
    for (int i = 1; i <= runs; ++i){
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}