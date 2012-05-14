using namespace std;
#include <iostream>
#include <algorithm>
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
#include <map>
#include <set>
#include <stack>

#define D(x) cout << #x " = " << (x) << endl
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); x++)
#define For (i, a, b) for (int i = (a); i < (b); i++)

const int MAXN = 1024;


int weight[MAXN];
int dl[MAXN], dr[MAXN];
int L[MAXN], R[MAXN], P[MAXN];

bool down(int u) {
    int c = weight[u];
    assert(c != -1);
    
    if (L[u] != -1 and R[u] != -1) {
        
        int l = L[u];
        int r = R[u];
        
        weight[l] = dr[u] * c;
        if (weight[l] % (dr[u] + dl[u]) != 0) return false;
        weight[l] /= (dr[u] + dl[u]);
        
        
        weight[r] = dl[u] * c;
        if (weight[r] % (dr[u] + dl[u]) != 0) return false;
        weight[r] /= (dr[u] + dl[u]);
        
        if (!down(l)) return false;
        if (!down(r)) return false;
        
    }
    
    return true;
}

bool check(int first, int w) {
    for (int i = 0; i < MAXN; ++i) {
        weight[i] = -1;
    }
    
    weight[first] = w;
    assert(L[first] == -1 and R[first] == -1);
    
    int cur = first;
    while  (P[cur] != -1) {
        int p = P[cur];
        
        if (cur == L[p]) { // soy x
            weight[p] = (dr[p] + dl[p]) * weight[cur];
            if (weight[p] % dr[p] != 0) return false;
            weight[p] /= dr[p];
            
            int b = R[p];
            weight[b] = dl[p] * weight[p];
            if (weight[b] % (dr[p] + dl[p]) != 0) return false;
            weight[b] /= (dr[p] + dl[p]);
            
            if (!down(b)) return false;
        } else { // soy y
            weight[p] = (dr[p] + dl[p]) * weight[cur];
            if (weight[p] % dl[p] != 0) return false;
            weight[p] /= dl[p];
            
            int b = L[p];
            weight[b] = dr[p] * weight[p];
            if (weight[b] % (dr[p] + dl[p]) != 0) return false;
            weight[b] /= (dr[p] + dl[p]);
            
            if (!down(b)) return false;
        }
        
        cur = p;
    }
    return true;
    
}

int main (){
    int n;
    int run = 1;
    
    while (cin >> n) {
        if (n == 0) break;
        
        for (int i = 0; i < MAXN; ++i) {
            P[i] = L[i] = R[i] = -1;
            dl[i] = dr[i] = -1;
            weight[i] = -1;
        }
        
        
        for (int i = 0; i < n; ++i) {
            cin >> dl[i] >> dr[i];
            char p, q; cin >> p >> q;
            int l, r; cin >> l >> r;
            l--;
            r--;
            if (p == 'W') l += n;
            if (q == 'W') r += n;
            L[i] = l;
            R[i] = r;
            
            P[l] = i;
            P[r] = i;
        }
        
        int first, bound; cin >> first >> bound;
        first--;
        first += n;
        
        printf("Case %d: ", run++);
        for (int w = bound; ; ++w) {
            if (check(first, w)) {
                int sum = 0;
                for (int i = 0; i < MAXN; ++i) {
                    if (P[i] == -1) {
                        sum += weight[i];                        
                        break;
                    }
                }
                
                D(weight[first]);
                
                printf("%d\n", sum);
                
                break;
            }
        }
        
    }
    return 0;
}
