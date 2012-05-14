// Andrés Mejía

// Accepted, just to see how much faster is scanf compared to cin.
// 0.080s.

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

int main(){
    int runs; scanf("%d", &runs);
    for (int run = 1; run <= runs; ++run) {
        int rows, cols; scanf("%d %d", &rows, &cols);
        int nim_sum = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int coins; scanf("%d", &coins);
                if ((rows - i + cols - j) % 2 == 1) { // white cell
                    nim_sum ^= coins;
                }
            }
        }
        printf("Case %d: %s\n", run, nim_sum == 0 ? "lose" : "win");
    }
    return 0;
}