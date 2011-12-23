// Andrés Mejía
// Memory Limit. Fuck.
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

const int MAXN = 2000002;

char data_forwards[2 * MAXN], data_backwards[2 * MAXN];
int length[2 * MAXN];

char * A[MAXN], * B[MAXN]; // A[i] = String, B[i] = String reversed

int times[MAXN + 1][2], states;
int border[MAXN + 1];
int next[MAXN + 1][26];

void insert(char * s, int n, int side) {
    int cur = 1, i;
    for (i = 0; i < n; ++i) {
        char c = s[i] - 'a';
        int move = next[cur][c];
        if (move == 0) break;
        cur = move;
    }
    for (; i < n; ++i) {
        char c = s[i] - 'a';
        next[cur][c] = ++states;
        cur = states;
    }
    times[cur][side]++;
}

long long count1(int W) {
    long long ans = 0;
    
    for (int k = 0; k < W; ++k) {
        int n = length[k];
        char * s = B[k];
        
        border[0] = 0;
        for (int i = 1, len = 0; i < n; ++i) {
            while (len > 0 and s[i] != s[len]) len = border[len - 1];
            if (s[i] == s[len]) len++;
            border[i] = len;
        }
        
        int len = 0; // $
        for (int i = 0; i < n; ++i) {
            while (len > 0 and A[k][i] != s[len]) len = border[len - 1];
            if (A[k][i] == s[len]) len++;
        }
        
        // len is the longest border of B[k]$A[k]
        if (len == n) len = border[len - 1];
        
        int cur = 1, matched = 0;
        while (true) {
            while (matched < n - len) {
                cur = next[cur][A[k][matched] - 'a'];
                matched++;
            }
            ans += times[cur][1];
            if (len == 0) break;
            len = border[len - 1];
        }
    }
    return ans;
}

long long count2(int W) {
    long long ans = 0;
    for (int k = 0; k < W; ++k) {
        int n = length[k];
        char * s = A[k];
        
        border[0] = 0;
        for (int i = 1, len = 0; i < n; ++i) {
            while (len > 0 and s[i] != s[len]) len = border[len - 1];
            if (s[i] == s[len]) len++;
            border[i] = len;
        }
        
        int len = 0; // $
        for (int i = 0; i < n; ++i) {
            while (len > 0 and B[k][i] != s[len]) len = border[len - 1];
            if (B[k][i] == s[len]) len++;
        }

        // len is the longest border of A[k]$B[k]
        if (len == n) len = border[len - 1];
        
        int cur = 1, matched = 0;
        while (len > 0) {
            while (matched < n - len) {
                cur = next[cur][A[k][n - 1 - matched] - 'a'];
                matched++;
            }
            ans += times[cur][0];
            len = border[len - 1];
        }
    }
    return ans;
}

int main(){
    int W;
    scanf("%d", &W);
    states = 1;
    
    char * next_forwards = data_forwards, * next_backwards = data_backwards;
    for (int i = 0; i < W; ++i) {
        int len; scanf("%d %s ", &len, next_forwards);
        assert(len > 0);
        
        length[i] = len;
        for (int j = 0; j < len; ++j) {
            next_backwards[j] = next_forwards[len - 1 - j];
        }
        A[i] = next_forwards;
        B[i] = next_backwards;
        next_forwards += len + 1;
        next_backwards += len + 1;
        
        insert(A[i], len, 0);
        insert(B[i], len, 1);
    }
    
    long long ans = count1(W) + count2(W);
    printf("%lld\n", ans);
    return 0;
}