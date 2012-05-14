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

const int MAXN = 1005;
int first[MAXN], second[MAXN];
int passed[MAXN];
int stars, n;


int turn() {
    for (int i = 0; i < n; ++i) {
        if (passed[i] == 0 and stars >= second[i]) {
            passed[i] = 2;
            return 2;
        }
    }
    
    for (int i = 0; i < n; ++i) {
        if (passed[i] == 1 and stars >= second[i]) {
            passed[i] = 2;
            return 1;
        }
    }
    
    int biggest_second = -1, which = -1;
    
    for (int i = 0; i < n; ++i) {
        assert(passed[i] == 2 or passed[i] == 0 or passed[i] == 1 and stars < second[i]);
        if (passed[i] == 0) {
            if (stars >= first[i] and second[i] > biggest_second) {
                biggest_second = second[i];
                which = i;
            }
        }
    }
    
    if (biggest_second < 0) return 0;
    assert(stars < biggest_second);
    
    passed[which] = 1;
    return 1;
}


void solve() {
    cin >> n;
    
    stars = 0;
    for (int i = 0; i < n; ++i) {
        cin >> first[i] >> second[i];
        passed[i] = 0;
    }
    
    int rounds = 0;
    while (true){
        int add = turn();
        if (add == 0) break;
        stars += add;
        rounds++;
    }
    // check if passed all levels
    for (int i = 0; i < n; ++i) {
        if (passed[i] < 2) {
            puts("Too Bad");
            return;
        }
    }
    printf("%d\n", rounds);
}

int main(){
    int T; cin >> T;
    for (int run = 1; run <= T; ++run) {
        printf("Case #%d: ", run);
        solve();
    }
    return 0;
}