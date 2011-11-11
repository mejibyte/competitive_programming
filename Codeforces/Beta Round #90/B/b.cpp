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

int prof[105];
bool used[105];
set< vector<int> > seen;

int main(){
    int n, k;
    while (cin >> n >> k) {
        memset(used, 0, sizeof used);
        seen.clear();
        For(i, 0, n) cin >> prof[i];
        
        int ans_min = 1<<28, ans_max = -(1<<28);
        
        int q; cin >> q;
        while (q--) {
            int sum = 0;
            vector<int> card;
            for (int i = 0; i < (n/k); ++i) {
                int x; cin >> x; x--;
                used[x] = true;
                sum += prof[x];
                card.push_back(x);
            }
            sort(card.begin(), card.end());
            seen.insert(card);
            ans_min = min(sum, ans_min);
            ans_max = max(sum, ans_max);
        }
        
        vector<int> unused;
        For(i, 0, n) if (!used[i]) unused.push_back(prof[i]);
        sort(unused.begin(), unused.end());
        if (unused.size() >= (n/k) and seen.size() < k) {
            assert(unused.size() >= (n/k));
            int small = 0, big = 0;
            for (int i = 0; i < (n/k); ++i) small += unused[i];
            for (int i = 0; i < (n/k); ++i) big += unused[unused.size() - 1 - i];
            ans_min = min(small, ans_min);
            ans_min = min(big, ans_min);
            
            ans_max = max(small, ans_max);
            ans_max = max(big, ans_max);
        }
        int f = n / k;
        printf("%.12lf %.12lf\n", 1.0 * ans_min / f, 1.0 * ans_max / f);
    }
    return 0;
}