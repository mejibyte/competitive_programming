using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

#define D(x) cout << #x " = " << (x) << endl

#define foreach(it, v) for (typeof v.begin() it = v.begin(); it != v.end(); ++it)

const int MAXV = 23;

vector<int> options[MAXV];

int sum[1 << 22];
bool dp[2][1 << 22];

int v[MAXV + 3];
int prefix_sum[MAXV + 3];

void print(int mask) {
    for (int i = 0; i < 32; ++i) {
        if (mask & (1 << i)) printf("%d ", i + 1);
    }
    puts("");
}

int main(){
    
    sum[0] = 0;
    for (int m = 1; m < (1 << 22); ++m) {
        int bit = __builtin_ctz(m);
        sum[m] = (bit + 1) + sum[m - (m & -m)];
       //sum[m] = 0;
       //for (int j = 0; j < 22; ++j) {
       //     if (m & (1 << j)) sum[m] += (j + 1);     
       //}
        
       if (sum[m] < MAXV) options[sum[m]].push_back(m);
    }
     
    
    int run = 1;
    
    int n, t;
    while (scanf("%d %d", &n, &t) == 2) {
        if (n == 0 and t == 0) break;   
        
        prefix_sum[0] = 0;
        for (int i = 1; i <= t; ++i) {
            scanf("%d", &v[i]); 
            prefix_sum[i] = v[i];
            if (i > 1) prefix_sum[i] += prefix_sum[i - 1];
        }
        
        int all = (1 << n) - 1;
        
        const int bad = INT_MIN + 1;
    
        int cur = 0, next = 1;
        for (int m = 1; m <= all; ++m) dp[cur][m] = false;   
        dp[cur][0] = true;
        
        int ans = 0;
        for (int i = 1; i <= t; ++i) {
            for (int s = all; s >= 0; --s) {
                dp[next][s] = false;
                
                //if (dp[cur][s]) ans = max(ans, __builtin_popcount(s));
            }
            for (int s = all; s >= 0; --s) {
                if (!dp[cur][s]) continue;
                //assert(sum[s] == prefix_sum[i - 1]);
                //if (sum[s] != prefix_sum[i - 1]) continue;
                //printf("on i = %d, s = %d, sum[s] = %d\n", i, s, sum[s]);
    
                //assert(v[i] < MAXV);
                for (int j = 0; j < options[v[i]].size(); ++j) {
                    int take = options[v[i]][j];
                    if (take > all) continue;                    
                    if ((take & s) != 0) continue;
                    //assert(take > 0);
                    //assert(sum[take] == v[i]);
                    
                    //printf("i = %d, take = %d, sum[take] = %d\n", i, take, sum[take]);
                    
                    dp[next][s | take] = true;
                    int score = __builtin_popcount(s | take);
                    if (score > ans) ans = score;
                }                
            }
            next ^= 1, cur ^= 1;
        }
        //for (int s = 0; s <= all; ++s) if (dp[cur][s]) ans = max(ans, __builtin_popcount(dp[cur][s]));
        printf("Game %d: %d\n", run++, ans);   
    }
    return 0;
}
