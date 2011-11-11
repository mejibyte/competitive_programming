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
int arr[MAXN], tree[MAXN];

int increase(int where) {
    assert(where > 0);
    while (where < MAXN) {
        tree[where]++;
        where += where & -where;
    }
}

int sum(int where) {
    assert(where > 0);
    int sum = 0;
    while (where > 0) {
        sum += tree[where];
        where -= where & -where;
    }
    return sum;
}

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", arr + i);
    }
    assert(n % 2 == 0);

    long long ans = 0;

    // First pass
    for (int i = 0; i < n; ) {
        int j = i + 1;
        while (j < n and arr[j - 1] > arr[j]) j++;
        if (i + 1 < j) {
            ans++;
            reverse(arr + i, arr + j);
        }
        i = j;
    }

    for (int i = 0; i < n; ++i) {
        // we need sum(a[i], n]
        ans += sum(n) - sum(arr[i]);
        increase(arr[i]);
    }

    printf("%lld\n", ans);
    return 0;
}