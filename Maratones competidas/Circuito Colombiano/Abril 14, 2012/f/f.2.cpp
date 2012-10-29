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
       if (sum[m] < MAXV) options[sum[m]].push_back(m);
    }
     
    
    int run = 1;
    
    int n, t;
    while (scanf("%d %d", &n, &t) == 2) {
        if (n == 0 and t == 0) break;   

        for (int i = 1; i <= t; ++i) {
            scanf("%d", &v[i]); 
        }
        
        int all = (1 << n) - 1;
    
        int cur = 0, next = 1;
        for (int m = 1; m <= all; ++m) dp[cur][m] = false;
        dp[cur][0] = true;
        
        int ans = 0;
        for (int i = 1; i <= t; ++i) {
            for (int s = all; s >= 0; --s) {
                dp[next][s] = false;
            }
            for (int s = all; s >= 0; --s) {
                if (!dp[cur][s]) continue;
                for (int j = 0; j < options[v[i]].size(); ++j) {
                    int take = options[v[i]][j];
                    if (take > all) break;
                    if ((take & s) != 0) continue;
                    dp[next][s | take] = true;
                    int score = __builtin_popcount(s | take);
                    if (score > ans) ans = score;
                }                
            }
            next ^= 1, cur ^= 1;
        }
        printf("Game %d: %d\n", run++, ans);   
    }
    return 0;
}
