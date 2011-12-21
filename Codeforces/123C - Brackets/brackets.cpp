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

const int MAXN = 205;

int priority[MAXN];
char str[MAXN];
int permutation[MAXN];
long long ways[MAXN][MAXN];

const long long INF = 1000000000000000001LL;

bool prioritary(int i, int j) {
    return priority[i] < priority[j];
}

void add(long long &where, const long long what) {
    where += what;
    if (where > INF) where = INF;
}

long long count(int len) {
    memset(ways, 0, sizeof ways);
    ways[0][0] = 1;
    for (int i = 0; i < len; ++i) {
        const char next = str[i];
        for (int open = 0; open <= len; ++open) {
            if (ways[i][open] == 0) continue;
            
            if (next != ')') add(ways[i + 1][open + 1],  ways[i][open]);
            if (next != '(' and open > 0) add(ways[i + 1][open - 1], ways[i][open]);
        }
    }
    return ways[len][0];
}

int main(){
    int n, m; long long k;
    cin >> n >> m >> k;
    assert(k < INF);
    assert((n + m) % 2 == 1);
    
    for (int i = 0; i < n + m - 1; ++i) {
        priority[i] = n * m + 1;
        permutation[i] = i;
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int x; cin >> x;
            priority[i + j] = min(priority[i + j], x);
        }
    }
    
    sort(permutation, permutation + n + m - 1, prioritary);
    for (int i = 0; i < n + m - 1; ++i) str[i] = '*';
    str[n + m - 1] = '\0';
    
    for (int i = 0; i < n + m - 1; ++i) {
        int pos = permutation[i];
        
        str[pos] = '(';
        long long add = count(n + m - 1);
        if (k > add) {
            str[pos] = ')';
            k -= add;
        }
    }
    assert(k == 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%c", str[i + j]);
        }
        printf("\n");
    }
    
    return 0;
}