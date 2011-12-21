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

const int MAXN = 100005;
int a[MAXN];

bool is_sorted(int n) {
    for (int i = 0; i < n - 1; ++i) {
        if (a[i] > a[i + 1]) return false;
    }
    return true;
}

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    
    long long ans = 0;
    while (!is_sorted(n)) {
        for (int i = 0; i < n; ) {
            int j = i + 1;
            while (j < n and a[j - 1] > a[j]) j++;
            reverse(a + i, a + j);
            if (i + 1 < j) ans++;
            i = j;
        }
    }
    printf("%lld\n", ans);
    return 0;
}