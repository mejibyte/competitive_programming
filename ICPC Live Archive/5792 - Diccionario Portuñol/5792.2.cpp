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

const int MAXS = 100005;

struct Trie {
    int g[MAXS][26];
    int stateCount;
    
    Trie() {
        clear();
    }
    
    void clear() {
        memset(g[0], -1, sizeof g[0]);
        stateCount = 1;
    }
    
    void add(char * s) {
        int state = 0; // root
        for (; *s; s++) {
            int next = (*s - 'a');
            if (g[state][next] == -1) {
                g[state][next] = stateCount;
                memset(g[stateCount], -1, sizeof g[stateCount]);
                stateCount++;
            }
            state = g[state][next];
        }
    }
};

Trie prefixTrie, suffixTrie;
int start[26];

void suffixDfs(int state, int depth) {
    for (int e = 0; e < 26; ++e) {
        if (suffixTrie.g[state][e] == -1) continue;
        if (depth >= 1) {
            start[e]++;
        }
        suffixDfs(suffixTrie.g[state][e], depth + 1);
    }
}

long long prefixDfs(int state, int depth) {
    long long ans = 0;
    if (depth >= 1) ans += suffixTrie.stateCount - 1;
    for (int e = 0; e < 26; ++e) {
        if (prefixTrie.g[state][e] == -1) continue;
        if (depth >= 1) {
            ans -= start[e];
        }
        ans += prefixDfs(prefixTrie.g[state][e], depth + 1);
    }
    return ans;
}

int main(){
    int P, S;
    while (scanf("%d %d ", &P, &S) == 2) {
        if (P == 0 and S == 0) break;
        
        prefixTrie.clear();
        suffixTrie.clear();
        for (int i = 0; i < 26; ++i) start[i] = 0;
        
        static char buffer[1024];
        for (int i = 0; i < P; ++i) {
            gets(buffer);
            prefixTrie.add(buffer);
        }
        for (int i = 0; i < S; ++i) {
            gets(buffer);
            int n = strlen(buffer);
            reverse(buffer, buffer + n);
            suffixTrie.add(buffer);
        }
        suffixDfs(0, 0);
        long long ans = prefixDfs(0, 0);
        
        printf("%lld\n", ans);
        
    }

    
    return 0;
}