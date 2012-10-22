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

typedef long long Int;

Int tax[1005];

Int cost(const string &s) {
    Int ans = 0;
    for (int i = 0; i < s.size(); ++i) if (s[i] == '1') ans += tax[i];
    return ans;
}

void solve(int n) {
    string start, end; cin >> start >> end;
    for (int i = 0; i < n; ++i) cin >> tax[i];
    
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (tax[i] < tax[j]) { // sort from greater to smaller
                swap(tax[i], tax[j]);
                swap(start[i], start[j]);
                swap(end[i], end[j]);
            }
        }
    }
    
    vector<Int> w;
    Int current_cost = cost(start);
    w.push_back(current_cost);
    for (int i = 0; i < n; ++i) {
        if (start[i] == '1' and end[i] == '0') {
            current_cost -= tax[i];
            w.push_back(current_cost);
        }
    }
    int limit = w.size();
    for (int i = n - 1; i >= 0; --i) {
        if (start[i] == '0' and end[i] == '1') {
            current_cost += tax[i];
            w.push_back(current_cost);
        }
    }
    
    for (int k = n - 1; k >= 0; --k) {
        if (start[k] == '1' and end[k] == '1') {
            
            int i = limit - 1;
            while (i > 0 and w[i - 1] - w[i] <= tax[k]) i--;
            
            int j = limit - 1;
            while (j < w.size() - 1 and w[j + 1] - w[j] <= tax[k]) j++;

            printf("k = %d: i = %d, j = %d\n", k, i, j);            
            
            if (0 <= i and j < w.size() and w[i]+w[j] - 1LL*(j-i+1)*tax[k] <= 0) {
                
                for (int p = i + 1; p < j; ++p) {
                    w[p] -= tax[k];
                }

                w.insert(w.begin() + j, w[j] - tax[k]);
                w.insert(w.begin() + i + 1, w[i] - tax[k]);
                limit++;
            }
        }
    }
    
    Int ans = 0;
    for (int i = 1; i < w.size(); ++i) {
        ans += w[i];
//        D(w[i]);
    }
    cout << ans << endl;
}

int main(){
    int run = 1, n;
    while (cin >> n) {
        if (n == 0) break;
        printf("Case %d: ", run++);
        solve(n);
    }
    return 0;
}