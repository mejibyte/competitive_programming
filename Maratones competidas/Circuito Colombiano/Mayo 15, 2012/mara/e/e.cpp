using namespace std;
#include <iostream>
#include <algorithm>
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
#include <map>
#include <set>
#include <stack>

#define D(x) cout << #x " = " << (x) << endl
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); x++)
#define For (i, a, b) for (int i = (a); i < (b); i++)

long long dp[65];

int main (){
    int n, q, runs = 1;
    while (cin >> n >> q) {
        if (n == 0 and q == 0) break;
        
        vector<int> original;
        
        vector<int> weights;
        for (int k = 0; k < n; ++k) {
            int w, many; cin >> w >> many;
            while (many--) weights.push_back(w);
            original.push_back(w);
        }
            
        printf("Case %d:", runs++);
        
        n = weights.size();
      
        long long sum = 0; for (int i = 0; i < n; ++i) sum += weights[i];
        assert(sum <= 60);
        
        map<int, long long> ans;
        
        for (int out = 0; out < n; ++out) {
            if (out - 1 >= 0 and weights[out - 1] == weights[out]) continue;
            
            vector<int> without;
            for (int i = 0; i < n; ++i) if (i != out) without.push_back(weights[i]);
            
            memset(dp, 0, sizeof dp);
            dp[0] = 1;
            for (int i = 0; i < without.size(); ++i) {
                int v = without[i];
                for (int s = sum; s >= v; --s) {
                    dp[s] += dp[s - v];
                }
            }
            
            long long cnt = 0;
            int v = weights[out];
            
            for (int s = 0; s <= sum; ++s) {
                if (s + v >= q and s < q) {
                    cnt += dp[s];
                }
            }
            
            ans[v] = cnt;   
        }
        
        for (int i = 0; i < original.size(); ++i) {
            int v = original[i];
            assert(ans.count(v));
            cout << " " << ans[v];
        }
        cout << endl;
    
    }

    return 0;
}
