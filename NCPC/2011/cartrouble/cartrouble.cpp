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

#include <bitset>


const int MAXN = 1005;
vector<int> g[MAXN];
vector<int> gt[MAXN];
vector<int> order;
bool v1[MAXN];
bool v2[MAXN];
int n;


void dfs1(int curr) {
    v1[curr] = true;
    for (int i = 0; i < g[curr].size(); i++){
        int next = g[curr][i];
        if (!v1[next]) dfs1(next);
    }
}

void dfs2(int curr){
    v2[curr] = true;
    for (int i = 0; i < gt[curr].size(); i++){
        int next = gt[curr][i];
        if (!v2[next]) dfs2(next);
    }
}



void solve() {
    bool good = true;
    
    vector<string> trapped, unreach;
    static char buf[1024];
    foreach(k, order) {
        int u = *k;
        //if (v1[u] and v2[u]) continue;
        
        if (!v2[u]) {
            sprintf(buf, "TRAPPED %d", u);
            trapped.push_back(string(buf));
        }
        
        if (!v1[u]){
            sprintf(buf, "UNREACHABLE %d", u);
            unreach.push_back(string(buf));
        }
    }
    
   
    if (trapped.size() + unreach.size() == 0) {
        puts("NO PROBLEMS");
    } else {
        foreach(k, trapped) puts(k->c_str());
        foreach(k, unreach) puts(k->c_str());
    }
}

int main(){
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int who, size;
        cin >> who >> size;
        order.push_back(who);
        for (int j = 0; j < size; ++j) {
            int to; cin >> to;
            g[who].push_back(to);
            gt[to].push_back(who);
        }
    }
    
    dfs1(0);
    dfs2(0);
    solve();
    return 0;
}
