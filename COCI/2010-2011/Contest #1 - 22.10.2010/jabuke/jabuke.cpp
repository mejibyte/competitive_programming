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

int main(){
    int n, m;
    cin >> n >> m;
    int ans = 0;
    int left = 1, right = m;
    int j; cin >> j;
    for (int i = 0; i < j; ++i) {
        int k; cin >> k;
        while (k < left) {
            left--;
            right--;
            ans++;
        }
        while (right < k) {
            right++;
            left++;
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}