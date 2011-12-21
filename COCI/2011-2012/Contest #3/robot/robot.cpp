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

vector<int> X, Y;

void print(vector<int> v) {
    for (int i = 0; i < v.size(); ++i) printf("%d ", v[i]);
    puts("");
}

long long smaller(int cur, const vector<int> &v) {
    long long ans = lower_bound(v.begin(), v.end(), cur) - v.begin();
    //printf("smaller: "); print(v); D(cur); D(ans);
    return ans;
}

long long bigger(int cur, const vector<int> &v) {
    long long ans = v.end() - upper_bound(v.begin(), v.end(), cur);
    //printf("bigger: "); print(v); D(cur); D(ans);
    return ans;

}

long long equal(int cur, const vector<int> &v) {
    long long ans = upper_bound(v.begin(), v.end(), cur) - lower_bound(v.begin(), v.end(), cur);
    //printf("equal: "); print(v); D(cur); D(ans);
    return ans;
}

int main(){
    int n, m; scanf("%d %d", &n, &m);
    long long score = 0;
    for (int i = 0; i < n; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        X.push_back(u); Y.push_back(v);
        score += abs(u) + abs(v);
    }
    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());

    int cx = 0, cy = 0;
    for (int k = 0; k < m; ++k) {
        char next; scanf(" %c ", &next);
        
        if (next == 'S') {
            score += smaller(cy, Y) + equal(cy, Y) - bigger(cy, Y);
            cy++;
        }
        if (next == 'I') {
            score += smaller(cx, X) + equal(cx, X) - bigger(cx, X);
            cx++;
        }
        if (next == 'J') {
            score += bigger(cy, Y) + equal(cy, Y) - smaller(cy, Y);
            cy--;
        }
        if (next == 'Z') {
            score += bigger(cx, X) + equal(cx, X) - smaller(cx, X);
            cx--;
        }
        printf("%lld\n", score);
    }
    return 0;
}