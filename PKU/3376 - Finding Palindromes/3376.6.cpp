// Andrés Mejía
// Accepted, finally!
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

const int MAXS = 2 * MAXN + 1; // Maximum number of states in the trie
const int MAXE = 2 * MAXN + 1; // Maximum number of edges in the trie

char data_forwards[2 * MAXN], data_backwards[2 * MAXN];

char * A[MAXN], * B[MAXN]; // A[i] = String, B[i] = String reversed

int border[MAXN];
int length[MAXN];
int times[MAXS][2];

int first[MAXS];
int next[MAXE];
int point[MAXE];
char label[MAXE];
int states, edges;

// If we are on state 'cur' and the next input character is 'c', 
// returns what state we move to.
inline int nextState(int cur, char c) {
    for (int e = first[cur]; e > 0; e = next[e]) {
        if (label[e] == c) return point[e];
    }
    return 0;
}

// Inserts string s into the trie.
void insert(char * s, int n, int side) {
    int cur = 1, i;
    for (i = 0; i < n; ++i) {
        char c = s[i];
        int move = nextState(cur, c);
        if (move == 0) break;
        cur = move;
    }
    for (; i < n; ++i) {
        char c = s[i];
        // Add a new edge and node.
        ++edges;
        ++states;
        
        point[edges] = states;
        label[edges] = c;
        next[edges] = first[cur];
        first[cur] = edges;
        
        cur = states;
    }
    times[cur][side]++;
}

inline void fillBorder(char * s, int n) {
    border[0] = 0;
    for (int i = 1, len = 0; i < n; ++i) {
        while (len > 0 and s[i] != s[len]) len = border[len - 1];
        if (s[i] == s[len]) len++;
        border[i] = len;
    }
}

// Returns the length of the longest border of string
// p$q.
// Both strings are of the same length, n.
// The concatenation is merely conceptual and doesn't
// really happen explicitely.
inline int lastBorder(char * p, char * q, int n) {
    int len = 0; // longest border of string "p$" (because $ doesn't appear anywhere else)
    for (int i = 0; i < n; ++i) { // Build next border as in KMP.
        while (len > 0 and q[i] != p[len]) len = border[len - 1];
        if (q[i] == p[len]) len++;
    }
    return len;
}

// For each word s[k] finds all the suffixes of s[k]
// that are palindrome and counts how many times the 
// complementary prefix appears reversed in the input.

// Also considers the suffix of length 0 (i.e. just 
// checks if the same string appears reversed as a word)
long long count1(int W) {
    long long ans = 0;
    
    for (int k = 0; k < W; ++k) {
        int n = length[k];
        
        fillBorder(B[k], n);
        int len = lastBorder(B[k], A[k], n);
        // len is the longest border of B[k]$A[k]
        if (len == n) len = border[len - 1];

        int cur = 1, matched = 0;
        while (true) {
            while (matched < n - len) {
                cur = nextState(cur, A[k][matched]);
                matched++;
            }
            ans += times[cur][1];
            if (len == 0) break;
            len = border[len - 1];
        }
    }
    return ans;
}

// Similar to count1, but considers prefixes instead
// of suffixes:
//
// For each word s[k] finds all the prefixes of s[k]
// that are palindrome and counts how many times the 
// complementary suffix appears reversed in the input.

// Does not consider a prefix of length 0, because that
// case was already counted in count1.
long long count2(int W) {
    long long ans = 0;
    for (int k = 0; k < W; ++k) {
        int n = length[k];

        fillBorder(A[k], n);
        int len = lastBorder(A[k], B[k], n);
        // len is the longest border of A[k]$B[k]
        if (len == n) len = border[len - 1];
        
        int cur = 1, matched = 0;
        while (len > 0) {
            while (matched < n - len) {
                cur = nextState(cur, A[k][n - 1 - matched]);
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
    states = 1, edges = 0;
    
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