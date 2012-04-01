//Equipo Poncho, carriel y ruana
// Sala Tayrona, maquina 140
using namespace std;
#include<algorithm>
#include<iostream>
#include<iterator>
#include<sstream>
#include<fstream>
#include<cassert>
#include<climits>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<deque>
#include<stack>
#include<list>
#include<map>
#include<set>

#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define foreach(x ,v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define D(x) cout << #x " = " << (x) << endl
#define V(a,n) for (int o=0; o<(n);++o) printf(#a "[%d] = %d\n", o, a[o])

const double EPS = 1e-9;

int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

#define dprintf false and printf

long long B, mod;
int MAXL;

long long bigmod(long long b, long long p) {
    long long mask = 1;
    long long pow2 = b % mod;
    long long r = 1;
    while (mask) {
        if (p & mask) r = (r * pow2) % mod;
        pow2 = (pow2 * pow2) % mod;
        mask <<= 1;
    }
    return r;
}

const int MAXN = 100005;
long long tree[MAXN + 1];
long long arr[MAXN + 1];

void add(int where, long long what) {
    long long pow = bigmod(B, where - 1);
    
    for (where++; where <= MAXL; where += where & -where) {
        tree[where] += pow * what;
        tree[where] %= mod;
        if (tree[where] < 0) tree[where] = (tree[where] + mod) % mod;
    }
}

long long query(int where) {
    long long sum = 0;
    for (where++; where > 0; where -= where & -where) {
        sum += tree[where];
    }
    return sum;
}

void set(int where, long long what) {
    add(where, -arr[where]);
    arr[where] = what;
    add(where, what);
}

int main() {

    int b, p, l, n, n_input;

    while(scanf("%d %d %d %d %d", &b, &p, &l, &n) == 4) {
        if(b == 0 and p == 0 and l == 0 and n == 0) break;
        B = b;
        mod = p;
        
        n_input = n;
        MAXL = l + 5;

        for (int i = 0; i < MAXL; ++i) tree[i] = arr[i] = 0;
        
        char cm;
        int i, v; 
        while(n_input--) {
            scanf(" %c %d %d", &cm, &i, &v);
            // responder al comando cm, i, v 
            if (cm == 'E') {
                ::set(l - i + 1, v);
            } else if (cm == 'H'){
                int right = l - i + 1;
                int left = l - v + 1;
                assert(left <= right);
                
            } 
        }
        puts("-");
    }
    return 0;
}
