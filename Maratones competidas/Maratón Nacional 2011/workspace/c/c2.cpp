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
set<int> bases[MAXBASES];

int B, D;
int bit[20]; // bit[i] = index of term i in the document

int memo[MAXBASES][1 << 16];


bool compatible(const set<int> &base) {
    foreach(x, base) {
        int term = *x;
        if (bit[term] == -1) return false; // base tiene un elemento que el doc no tiene
    }
    return true;
}

int maskOfBase(const set<int> &base) {
    int ans = 0;
    foreach(x, base){ 
        int term = *x;
        ans = ans | (1 << bit[term]);
    }
    return ans;
}
int docSize;

int f(int b, int mask, const set<int> &doc) {
    int n = docSize;
    
    if (b == B) { // Vi todas las bases
        return (mask == ((1 << n) - 1) ? 0 : oo);
    }
    //assert(b < B);
    //printf("b = %d\n", b);
    if (memo[b][mask] != -1) return memo[b][mask];
    
    if (!compatible(bases[b])) {
        return memo[b][mask] = f(b + 1, mask, doc);
    }
    
    //assert(compatible(bases[b]));
    
    // cojo esta base
    int ans = f(b + 1, mask | maskOfBase(bases[b]), doc) + 1;
    
    // no la cojo
    ans = min(ans, f(b + 1, mask, doc));
    return memo[b][mask] = ans;
}

void solve(const set<int> &doc) {
    //puts("doc: "); foreach(x, doc) printf("%d ", *x); puts("");
    memset(bit, -1, sizeof bit);
    
    int k = 0;
    foreach(x, doc) {
        int term = *x;
        bit[term] = k++;
    }
    
    //For(i, 0, B) if (compatible(bases[i])) printf("Base i=%d: %d\n", i, maskOfBase(bases[i]));
    
  //  for (int i = 0; i < 16; ++i) {
//        printf("bit[%d] = %d\n", i, bit[i]);
//    }
    
    int ans = f(0, 0, doc);
    if (ans >= oo) ans = 0;
    printf("%d", ans);
}

int main(){
    freopen(INPUT_FILE ".in", "r", stdin);
    while (cin >> B >> D) {
        if (B == 0 and D == 0) break;
        for (int i = 0; i < B; ++i) {
            bases[i].clear();
            int k; cin >> k;
            while (k--) {
                int x; cin >> x; x--;
                bases[i].insert(x);
            }
        }
        
        for (int j = 0; j < D; ++j) {
            set<int> doc;
            int k; cin >> k;
            while (k--) {
                int x; cin >> x; x--;
                doc.insert(x);
            }
            docSize = doc.size();            
            for (int b = 0; b < B; ++b) {
                for (int mask = 0; mask < (1 << docSize); ++mask) {
                    memo[b][mask] = -1;
                }
            }
            solve(doc);
            if (j + 1 < D) printf(" ");
        }
        puts("");
        
    }
    return 0;

}
