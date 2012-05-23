// Growing Strings from Latin America 2010
// Andrés Mejía

// Accepted in 4.6s.
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <cstdio>
#include <cassert>
using namespace std;

#define D(x) cerr << #x " = " << (x) << endl

namespace Aho {
    const int MAXN = 1000005;
    map<char, int> g[MAXN];
    int f[MAXN]; // failure
    vector<int> output[MAXN];
    int n; // state count
    
    // n should be the sum of the lenghts of all substrings
    void reset() {
        n = 1;
        g[0].clear();
        output[0].clear();
        f[0] = 0;
    }
    
    void add(const char * s, int id) {
        int state = 0;
        for (int i = 0; s[i]; i++) {
            char c = s[i];
            if (g[state].count(c) == 0) {
                g[state][c] = n;
                g[n].clear();
                output[n].clear();
                f[n] = -1;
                n++;
            }
            state = g[state][c];
        }
        output[state].push_back(id);
    }
    
    void prepare() { // the BFS step
        queue<int> q;
        f[0] = 0;
        for (char c = 'a'; c <= 'z'; ++c) {
            if (g[0].count(c) == 0) {
                g[0][c] = 0;
            } else {
                int s = g[0][c];
                f[s] = 0;
                q.push(s);
            }
        }
        
        while (q.size() > 0) {
            int u = q.front(); q.pop();
            for (map<char, int>::iterator i = g[u].begin(); i != g[u].end(); ++i) {
                char label = i->first;
                int node = i->second;
                f[node] = f[u];
                while (g[f[node]].count(label) == 0) {
                    f[node] = f[f[node]];
                }
                f[node] = g[f[node]][label];
                output[node].insert(output[node].end(), output[f[node]].begin(), output[f[node]].end());
                q.push(node);
            }
        }   
    }
    
    int next_state(int state, char label) {
        while (g[state].count(label) == 0) {
            state = f[state];
        }
        return g[state][label];
    }
}

char buffer[1024];

const int MAXS = 10005;
vector<int> graph[MAXS];
int memo[MAXS];

int best_chain(int u) {
    if (memo[u] != -1) return memo[u];
    int ans = 1;
    for (int k = 0; k < graph[u].size(); ++k) {
        int v = graph[u][k];
        ans = max(ans, best_chain(v) + 1);
    }
    return memo[u] = ans;
}

int main() {
    int n;
    while (scanf("%d ", &n) == 1) {
        if (n == 0) break;
        
        vector<string> plants;
        for (int i = 0; i < n; ++i) {
            scanf("%s ", buffer);
            plants.push_back(string(buffer));
            assert(plants.back().size() <= 1000);
            graph[i].clear();
            memo[i] = -1;
        }
        
        Aho::reset();
        for (int i = 0; i < n; ++i) {
            Aho::add(plants[i].c_str(), i);
        }
        Aho::prepare();   
//        for (int i = 0; i < Aho::n; ++i) {
//            printf("f[%d] = %d\n", i, Aho::f[i]);
//            for (int k = 0; k < Aho::output[i].size(); ++k) {
//                printf("  --> %s\n", plants[Aho::output[i][k]].c_str());
//            }
//        }

        for (int i = 0; i < n; ++i) {
            const string &s = plants[i];
            int state = 0;
            for (int k = 0; k < s.size(); ++k) {
                char next = s[k];
                state = Aho::next_state(state, next);
                for (int e = 0; e < Aho::output[state].size(); ++e) {
                    int to = Aho::output[state][e];
                    if (plants[to].size() < s.size()) { // found a proper substring
                        graph[i].push_back(to);
                    }
                }
            }
        }
        
        D(1.0*clock() / CLOCKS_PER_SEC);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans = max(ans, best_chain(i));
        }
        D(1.0*clock() / CLOCKS_PER_SEC);        
        printf("%d\n", ans);
    }
    return 0;
}
