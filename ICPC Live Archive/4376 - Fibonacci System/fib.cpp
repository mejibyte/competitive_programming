// Andrés Mejía

// Accepted

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

const long long TEN15 = 1000000000000005LL;

vector<long long> fib;

// cuantos dígitos en total he escrito si he escrito los números [1, k]
long long digits(long long k) {
    long long ans = 0;
    for (int i = 1; fib[i] <= k; ++i) {
        long long to = min(fib[i + 1], k + 1);
        ans += (to - fib[i]) * i;
    }
    return ans;
}

vector<int> to_fib(long long k) {
    assert(k > 0);
    vector<int> ans;
    for (int i = fib.size() - 1; i >= 0; --i) {
        if (k >= fib[i]) {
            k -= fib[i];
            ans.push_back(1);
        } else {
            ans.push_back(0);
        }
    }
    while (ans[0] == 0) ans.erase(ans.begin());
    ans.pop_back(); // fib[0]
    return ans;
}

bool visited[100][2][2];
pair<long long, long long> memo[100][2][2];

// retorna (unos, # numeros)
pair<long long, long long> ones(int i, bool smaller, bool last_one, const vector<int> &b) {
    int size = b.size();
    if (i == size) {
        return make_pair(0, 1);
    }
    if (visited[i][smaller][last_one]) return memo[i][smaller][last_one];
    visited[i][smaller][last_one] = true;
    
    long long o = 0, m = 0;
    
    o += ones(i + 1, smaller or b[i] == 1, false, b).first;
    m += ones(i + 1, smaller or b[i] == 1, false, b).second;
    
    if (!last_one and (smaller or b[i] == 1)) {
        o += ones(i + 1, smaller, true, b).second;
        o += ones(i + 1, smaller, true, b).first;
        m += ones(i + 1, smaller, true, b).second;
    }
    return memo[i][smaller][last_one] = make_pair(o, m);
}

void solve(long long n) {
    if (n == 0) {
        puts("0");
        return;
    }
    
    long long low = 1, high = n;
    while (low < high) {
        long long mid = (low + high + 1) / 2;
        if (digits(mid) <= n) {
            low = mid;
        } else {
            high = mid - 1;
        }
    }
    long long last = low;
    assert(digits(last) <= n);
    
    long long extra = 0;
    
    vector<int> next = to_fib(last + 1);
    for (long long i = 0, bound = n - digits(last); i < bound; ++i) {
        extra += next[i];
    }
    
    vector<int> b = to_fib(last);
    //D(last);
    //For(i, 0, b.size()) printf("%d", b[i]); puts("");

    memset(visited, false, sizeof visited);
    pair<long long, long long> ans = ones(0, 0, 0, b);
//    D(ans.first); D(extra);
    cout << ans.first + extra << endl;
}

int main(){
    fib.assign(2, 1);
    while (fib.back() < TEN15) {
        fib.push_back(fib.back() + fib[fib.size() - 2]);
    }
    long long n;
    while (cin >> n) {
        solve(n);
    }
    return 0;
}