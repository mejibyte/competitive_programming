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

const int MAXN = 100005;
long long P[MAXN], S[MAXN];

void add(long long * tree, int at, int what) {
    for (at++; at < MAXN; at += at & -at) {
        tree[at] += what;
    }
}

long long get(long long * tree, int at) {
    long long ans = 0;
    for (at++; at > 0; at -= at & -at) {
        ans += tree[at];
    }
    return ans;
}

int arr[MAXN];

int main(){
    int n; cin >> n;
    For(i, 0, n) cin >> arr[i];

    long long ans = 0;
    for (int i = n - 1; i >= 0; --i) {
        int a = arr[i];
        ans += get(P, a - 1);
        add(P, a, get(S, a - 1));
        add(S, a, 1);
    }
    cout << ans << endl;
    return 0;
}
