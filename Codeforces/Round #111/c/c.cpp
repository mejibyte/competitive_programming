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

int n;
map<int, int> f;

pair<int, int> solve(long long k) {
    pair<int, int> ans;
    foreach(p, f) {
        long long have = 1LL * p->second * n;
        if (have >= k) {
            ans.first = p->first;
            int times = p->second;
            foreach(p2, f) {
                long long have2 = 1LL * times * p2->second;
                if (have2 >= k) {
                    ans.second = p2->first;
                    break;
                } else {
                    k -= have2;
                }
            }
            break;
        } else {
            k -= have;
        }
    }
    return ans;
}

int main(){
    long long k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        f[a[i]]++;
    }
    pair<int, int> ans = solve(k);
    cout << ans.first << " " << ans.second << endl;
    return 0;
}