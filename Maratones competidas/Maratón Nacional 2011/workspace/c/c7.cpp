// Equipo Poncho, Carriel y Ruana
using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
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
#include <stack>
#include <list>
#include <map>
#include <set>

template <class T> string toStr(const T &x)
{ stringstream s; s << x; return s.str(); }
template <class T> int toInt(const T &x)
{ stringstream s; s << x; int r; s >> r; return r; }

#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define D(x) cout << #x " = " << (x) << endl;

const double EPS = 1e-9;

int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

#define INPUT_FILE "compression"

const int MAXBASES = 105, oo = 1 << 28;
int bases[MAXBASES];

int B, D;
int bit[20]; // bit[i] = index of term i in the document

int dp[MAXBASES][1 << 16];

int docSize;

void binary(int x){
    for (int i = 0; i < 16; ++i){
        printf("%d", !!(x & (1 << i)));
    }
}

int v[16];

bool canDelete(int base) {
    for (int j = 0; j < 16; ++j) {
        if (base & (1 << j)){
            if (v[j] <= 1) return false;
        }
    }
    return true;
}

bool noSolution(int doc) {
    for (int j = 0; j < 16; ++j) {
        if (doc & (1 << j)) {
            if (v[j] == 0) return true;
        }
    }
    return false;
}

void solve(int doc) {
    for (int i = 0; i < 16; ++i) {
        v[i] = 0;
    }
    int ans = 0;
    for (int i = 0; i < B; ++i) {
        if ((bases[i] | doc) == doc){
            //printf("took base i = %d\n", i);
            for (int j = 0; j < 16; ++j){
                if (bases[i] & (1 << j)) {
                    v[j]++;
                }
            }
            ans++;
        }
    }
    for (int i = 0; i < B; ++i) {
        if (canDelete(bases[i])) {
            ans--;
            //printf("removed base i = %d\n", i);
            for (int j = 0; j < 16; ++j) {
                if (bases[i] & (1 << j)) {
                    v[j]--;
                }
            }
        }
    }
    
    if (noSolution(doc)) {
        printf("0");
        return;
    }
    printf("%d", ans);
    
}

bool popcount(int a, int b) {
    return __builtin_popcount(a) < __builtin_popcount(b);
}

int main(){
    freopen(INPUT_FILE ".in", "r", stdin);
    while (cin >> B >> D) {
        if (B == 0 and D == 0) break;
        for (int i = 0; i < B; ++i) {
            bases[i] = 0;
            
            int k; cin >> k;
            while (k--) {
                int x; cin >> x; x--;
                bases[i] |= (1 << x);
            }
            //printf("base[i=%d] = %d\n", i, bases[i]);
        }
        sort(bases, bases + B, popcount);
        for (int j = 0; j < D; ++j) {
            int doc = 0;
            cin >> docSize;
            int k = docSize;
            while (k--) {
                int x; cin >> x; x--;
                doc |= (1 << x);
            }
            //printf("doc = %d\n", doc);
            solve(doc);
            if (j + 1 < D) printf(" ");
        }
        puts("");
        
    }
    return 0;

}
