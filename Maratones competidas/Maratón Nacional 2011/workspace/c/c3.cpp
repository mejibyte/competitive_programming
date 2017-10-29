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

int memo[MAXBASES][1 << 16];


int docSize;

int f(int b, int mask, int doc) {
    if (mask == doc) return 0;
    if (b == B) { // Vi todas las bases
        return (oo);
    }
    //assert(b < B);
    //printf("b = %d\n", b);
    if (memo[b][mask] != -1) return memo[b][mask];
    
    if ((bases[b] | doc) != doc) {
        return memo[b][mask] = f(b + 1, mask, doc);
    }
    
    //assert(compatible(bases[b]));
    
    // cojo esta base
    int ans = f(b + 1, mask | bases[b], doc) + 1;
    
    // no la cojo
    ans = min(ans, f(b + 1, mask, doc));
    return memo[b][mask] = ans;
}

void solve(int doc) {

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
            bases[i] = 0;
            
            int k; cin >> k;
            while (k--) {
                int x; cin >> x; x--;
                bases[i] |= (1 << x);
            }
            //printf("base[i=%d] = %d\n", i, bases[i]);
        }
        
        for (int j = 0; j < D; ++j) {
            int doc = 0;
            cin >> docSize;
            int k = docSize;
            while (k--) {
                int x; cin >> x; x--;
                doc |= (1 << x);
            }
            //printf("doc = %d\n", doc);     
            for (int b = 0; b < B; ++b) {
                for (int mask = 0; mask < (1 << 16); ++mask) {
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
