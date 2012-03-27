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

namespace IO {
   #define MAXBUFF (1<<18)
    char buffer[MAXBUFF], *p = buffer+MAXBUFF;

    inline char read_char() {
        if( p == buffer+MAXBUFF ) {
            fread( buffer, 1, MAXBUFF, stdin );
            p = buffer;
        }
        return *p++;
    }

    inline int read_signed_int() {
        char c;
        while( !isdigit(c = read_char()) and c != '-' );
        int sign = 1;
        if (c == '-') sign = -1, c = read_char();
        int ret = c-'0';
        while( isdigit(c = read_char()) ) ret = ret * 10 + c-'0';
        return ret * sign;
    }

    inline int read_unsigned_int() {
        char c;
        while( !isdigit(c = read_char()) );
        int ret = c-'0';
        while( isdigit(c = read_char()) ) ret = ret * 10 + c-'0';
        return ret;
    }
    
    // Reads a line into s and returns its length. Doesn't perform
    // any check for the size of s. If only stops reading when it
    // reaches a '\n'. If there's not one, it will fall into an infinite
    // loop.
    inline int gets(char * s) {
        int length = 0;
        char c;
        while ((c = read_char()) != '\n') {
            *s++ = c;
            length++;
        }
        *s = '\0';
        return length;
    }
}


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
    while (true) {
        P = IO::read_unsigned_int();
        S = IO::read_unsigned_int();
        if (P == 0 and S == 0) break;
        
        prefixTrie.clear();
        suffixTrie.clear();
        for (int i = 0; i < 26; ++i) start[i] = 0;
        
        static char buffer[1024];
        for (int i = 0; i < P; ++i) {
            IO::gets(buffer);
            prefixTrie.add(buffer);
        }
        for (int i = 0; i < S; ++i) {
            int n = IO::gets(buffer);
            reverse(buffer, buffer + n);
            suffixTrie.add(buffer);
        }
        suffixDfs(0, 0);
        long long ans = prefixDfs(0, 0);
        
        printf("%lld\n", ans);
        
    }

    
    return 0;
}