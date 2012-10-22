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

typedef long long ll;
bool visited[MAXN];

struct Frac {
    ll a, b;
    
    Frac(ll x, ll y) {
        a = x;
        b = y;
        long long g = __gcd(a, b);
        a /= g;
        b /= g;
    }
    
    Frac() {
        a = 0;
        b = 1;
    }
    
    Frac operator * (const Frac &t) const {
        long long up = a * t.a;
        long long down = b * t.b;
        return Frac(up, down);
    }
    
    void print() {
        cout << a << "/" << b << endl;
    }
    
};


Frac coef[MAXN];

void fill(int u) {
    visited[u] = true;
    if (L[u] == -1 or R[u] == -1) return;
    
    Frac k = Frac(dr[u], dr[u] + dl[u]);
    coef[L[u]] = coef[u] * k;
    fill(L[u]);
    
    k = Frac(dl[u], dr[u] + dl[u]);
    coef[R[u]] = coef[u] * k;
    fill(R[u]);
}

long long lcm(long long a, long long b) {
    long long g = __gcd(a, b);
    return a / g * b;
}

long long myCeil(ll a, ll b) {
    return (a + b - 1) / b;
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
        
        int root;
        for (int i = 0; i < MAXN; ++i) {
            if (P[i] == -1) {
                root = i;
                break;
            }
        }
        
        memset(visited, 0, sizeof visited);
        coef[root] = Frac(1, 1);
        fill(root);
           
        long long _lcm = -1;
        
        vector<int> hojas;
        
        
        for (int i = 0; i < MAXN; ++i) {
            if (!visited[i]) break;
            if (L[i] == -1 and R[i] == -1) {
                hojas.push_back(i);
            }
        }
            
        for (int k = 0; k < hojas.size(); ++k) {
            int h = hojas[k];
            
            if (_lcm == -1) _lcm = coef[h].b;
            else _lcm = lcm(_lcm, coef[h].b);
                
            //coef[h].print();
        }
        
        assert(first >= n);
        
        for (int times = 1; ; ++times) {
            long long valor = coef[first].a * times * _lcm;
            assert(valor % coef[first].b == 0);
            valor /= coef[first].b;
            if (valor >= bound) {
                cout << _lcm * times << endl;
                
                assert(times == myCeil(coef[first].b * bound, _lcm * coef[first].a));
                break;
            }
        }

    }
    return 0;
}
