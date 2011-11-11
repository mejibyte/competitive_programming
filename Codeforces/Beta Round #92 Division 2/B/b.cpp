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

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

int cnt[105];

int main(){
    int n;
    while (cin >> n) {
        memset(cnt, 0, sizeof cnt);
        for (int i = 0; i < n; ++i) {
            int x; cin >> x;
            cnt[x]++;
            assert(1 <= x and x <= 100);
        }
        int sum = 0;
        for (int i = 0; i <= 100; ++i) {
            sum += cnt[i] / 2;
        }
        printf("%d\n", sum / 2);
    }
    return 0;
}