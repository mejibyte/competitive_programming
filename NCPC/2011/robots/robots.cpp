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

const int MAXN = 1005;
string a [MAXN];
long long dp[MAXN][MAXN];
bool v[MAXN][MAXN];

const long long mod = (1LL << 31) - 1;

int n;

bool can (int i, int j){
    if (i < 0 or j < 0) return false;
    if (i >= n or j >= n) return false;
    if (a[i][j] == '#') return false;
    return true;
}

int di [] = {+1, 0, -1, 0};
int dj [] = {0, +1,  0,-1};

bool dfs(int i, int j, int size){
    //printf("Call dsf(%d, %d)\n", i, j);
    v[i][j] = true;
    if (i == n - 1 and j == n - 1) return true;
    bool found = false;
    for (int k = 0; k < size; k++){
        int ni = i + di[k];
        int nj = j + dj[k];
        if (can(ni, nj) and !v[ni][nj]) found |= dfs(ni, nj, size);
        if (found) break;
    }
    return found;
}

int main(){ 
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (!can(i, j)) continue;
            
            if (can(i + 1, j)) {
                dp[i + 1][j] += dp[i][j];
                dp[i + 1][j] %= mod;
            }
            if (can(i, j + 1)) {
                dp[i][j + 1] += dp[i][j];
                dp[i][j + 1] %= mod;
            }
        }
    }
    assert(mod == INT_MAX);
    
    if ( !dfs(0, 0, 2) ){
        memset(v, 0, sizeof v);
        assert(dp[n - 1][n - 1] == 0);
        if (dfs(0, 0, 4)) puts("THE GAME IS A LIE");
        else puts("INCONCEIVABLE");
    }else{
        assert(dp[n -1][n - 1] >= 0);
        cout << dp[n-1][n-1] << endl;
        
    }
    
    return 0;
}
