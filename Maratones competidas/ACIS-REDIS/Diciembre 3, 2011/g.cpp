using namespace std;
#include <algorithm>
#include <iostream>
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
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>

template <class T> string toStr(const T &x)
{ stringstream s; s << x; return s.str(); }
template <class T> int toInt(const T &x)
{ stringstream s; s << x; int r; s >> r; return r; }

#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); \
                           x != (v).end(); ++x)
#define D(x) cout << #x " = " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS){
    return( x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

#define INPUT_FILE "frosh"

const int MAXN = 1000010;

long long tree[MAXN];

void add(int where, long long what) {
    for (where++; where < MAXN; where += where & -where) {
        tree[where] += what;
    }
}

long long query(int where) {
    long long ans = 0;
    for (where++; where > 0; where -= where & -where) {
        ans += tree[where];
    }
    return ans;
}

int a[MAXN];
int all[MAXN]; 

int main(){
    freopen(INPUT_FILE ".in", "r", stdin); // Read from file
    memset(tree, 0, sizeof tree);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        all[i] = a[i];
    }
    sort(all, all + n);
    for (int i = 0; i < n; ++i) {
        int u = a[i];
        int rank = lower_bound( all, all + n, u ) - all;
        a[i] = rank;
        //D(a[i]);
    }
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        int u = a[i];
        ans += query(n + 1) - query(u);
        add(u, 1);
    }
    cout << ans << endl;
    return 0;
}
