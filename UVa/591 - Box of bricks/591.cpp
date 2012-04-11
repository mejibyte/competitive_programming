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

int main(){
    int n, run = 1;
    while (scanf("%d", &n) == 1 and n > 0) {
        vector<int> height(n);
        int average = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &height[i]);
            average += height[i];
        }
        assert(average % n == 0);
        average /= n;
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (height[i] > average) ans += height[i] - average;
        }
        printf("Set #%d\nThe minimum number of moves is %d.\n\n", run++, ans);
    }
    return 0;
}