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

char s [5005];
int p [5005]; // The predecesor of each node in the cycle
int v [5005];
int color [5005]; // (0, white), (1, grey), (2, black)
int n;

vector<int> graph [5005];

int dfs(int u);
//Check if the graph has a cycle. If it does, return a node in the cycle.
//If it doesn't return -1.
int find_cycle(){       
    int ans = -1;
    for (int u = 0; u < n and ans == -1; u++){
        if (color[u] == 0){// White
            ans = dfs(u);           
        }
    }
    return ans;
}

int dfs(int u){
    int ans = -1;
    color[u] = 1; //Paint gray
    for (int k = 0; k < graph[u].size() and ans == -1; k++){
        int j = graph[u][k];
        if (color[j] == 1) return j;
        if (color[j] == 0) ans = dfs(j);
    }
    color[u] = 2; //Paint black
    return ans;
}

vector <int> bfs(int init){
        // Initialize visited array
    for (int i = 0; i < n; i++) v[i] = -1;

    vector <int> ans;
    ans.push_back(init);    
    queue <int> q;  
    v[init] = 0;
    p[init] = -1;
    q.push(init);

    bool found = false;
    while(q.size() > 0 and !found){
        int curr = q.front();
        q.pop();
        for (int k = 0; k < graph[curr].size(); k++){
            int j = graph[curr][k];

            if (j == init){                                 
                ans.push_back(p[curr]);
                ans.push_back(curr);
                found = true;
                assert(v[curr] == 2);
                break;
            }
            if (v[j] != -1) continue;
            v[j] = v[curr] + 1;
            p[j] = curr;
            q.push(j);
        }
    }

    assert(ans.size() == 3);
    return ans;
}


//IDEA: If the graph has at least one cycle, then it has a cycle of length 3.
//PROOF:
// * The cycle can not be of length 1 (no self-loops).
// * The cycle can not be of lenght 2 (G[i][j] != G[j][i])
// * Therefore the cycle has to be of length at least 3.
// * Lets assume the cycle has length more than 3. Let v1, v2 and v3 be the first
//   three nodes of the cycle. Therefore G[v1][v2] = G[v2][v3] = 1. By the config
//   of the graph, one of the following must happen:
//      * G[v3][v1] = 1 and we have a cycle of length 3.
//      * G[v1][v3] = 1 then we eliminate node v2 and reduce the cycle length by one.
//        We can do this last step many times until we get our length 3 cycle.

int main(){
    scanf("%d ", &n);
    for (int i = 0; i < n; i++){
        gets(s);
        for (int j = 0; j < n; ++j) {
            if (s[j] == '1') graph[i].push_back(j);
        }
    }
    int node = find_cycle();
    if (node != -1){
        vector <int> list = bfs(node);
        printf("%d %d %d\n", list[0] + 1, list[1] + 1, list[2] + 1);
    }else{
        puts("-1");
    }
    return 0;
}
