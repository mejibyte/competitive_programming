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

#include <bitset>

const int MAXN = 300005;

bitset<MAXN> high;
bitset<MAXN> low;

int main(){
    ios::sync_with_stdio(false);
    int n; cin >> n;
    
    high.reset();
    low.reset();
    for (int i = 0; i < n; ++i) high[i] = low[i] = true;
    
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    
    int lowCount = 0, highCount = 0;
    for (int i = 0; i < n; ++i) {
        if (i - 1 >= 0 and a[i - 1] < a[i]) low[i] = false;
        if (i - 1 >= 0 and a[i - 1] > a[i]) high[i] = false;
        if (i + 1 < n  and a[i + 1] < a[i]) low[i] = false;
        if (i + 1 < n  and a[i + 1] > a[i]) high[i] = false;
        
        assert(!high[i] or !low[i]);
        lowCount += low[i];
        highCount += high[i];
    }
    
    vector<int> have(n);
    for (int i = 0; i < n; ++i) cin >> have[i];
    sort(have.begin(), have.begin() + n);
    
    vector<int> L, H;
    assert(lowCount + highCount <= n);
    for (int i = 0; i < lowCount; ++i) {
        L.push_back(-have[i]);
    }
    for (int i = 0; i < highCount; ++i) {
        H.push_back(have[n - 1 - i]);
    }
    
    sort(L.begin(), L.end());
    sort(H.begin(), H.end());
    
    long long ans = 0;
    for (int i = 0; i < L.size(); ++i) ans += 2*L[i];
    for (int j = 0; j < H.size(); ++j) ans += 2*H[j];
    
    assert(low[0] + low[n - 1] <= L.size());
    assert(high[0] + high[n - 1] <= H.size());
    
    for (int i = 0; i < L.size() and i < low[0] + low[n - 1]; ++i) {
        ans -= L[i];
    }

    for (int i = 0; i < H.size() and i < high[0] + high[n - 1]; ++i) {
        ans -= H[i];
    }
    cout << ans << endl;
    
    if (high[0] and high[n - 1]) {
        swap(H[1], H.back());
    } else if (high[0] and low[n - 1]) {
        swap(L[0], L.back());
    } else if (low[0] and low[n - 1]) {
        swap(L[1], L.back());
    } else {
        assert(low[0] and high[n - 1]);
        swap(H[0], H.back());
    }
    
    for (int i = 0; i < L.size(); ++i) {
        L[i] = -L[i];
    }
    
    // puts("L: "); foreach(p, L) printf("%d ", *p); puts("");
    // puts("H: "); foreach(p, H) printf("%d ", *p); puts("");
    
    int nextLow = 0, nextHigh = 0, nextNormal = lowCount;
    vector<int> how(n);
    for (int i = 0; i < n; ++i) {
        if (!low[i] and !high[i]) {
            how[i] = have[nextNormal++];
        } else if (low[i]) {
            how[i] = L[nextLow++];
        } else {
            how[i] = H[nextHigh++];
        }
    }
    
    //puts("how before fixing: "); foreach(p, how) printf("%d ", *p); puts("");
    
    for (int i = 0; i < n - 1; ++i) {
        assert(high[i] or low[i]);
        int j = i + 1;
        while (!low[j] and !high[j]) j++;
        assert(j < n);
        int len = j - i;
        if (len > 2 and high[i] and low[j]) {
            reverse(how.begin() + i + 1, how.begin() + j);
        }
        
        i = j - 1;
    }
    
    //puts("how after fixing: "); foreach(p, how) printf("%d ", *p); puts("");
    
    for (int i = 0; i < n; ++i) {
        if (i > 0) cout << " ";
        cout << how[i];
    }
    cout << endl;
    return 0;
}