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

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

const int MAXN = 50005;
const int MAXTREE = 1 << 16;
int a [MAXN];
int tree [2 * MAXTREE];
map <int, int> year2int;
int n;

int query(int u, int l, int r, int p, int q){
    // printf("Call query u = %d, l = %d, r = %d, p = %d, q = %d\n", u, l, r, p, q);
    assert (p <= q and l <= r);
    
    // Node outside the query
    if (q < l or r < p) return -1;
    
    // Node totally inside the query
    if (p <= l and r <= q) return tree[u];
    
    // Node partiall inside the query
    int m = (r + l) / 2;
    int left = query(2 * u + 1, l, m, p, q);
    int right = query(2 * u + 2, m + 1, r, p, q);
    
    return max(left, right);
}

void build(int u, int l, int r){
    if (l == r){
        tree[u] = a[l];
        return;
    }
    int m = (l + r) / 2;
    build(2 * u + 1, l, m);
    build(2 * u + 2, m + 1, r);
    tree[u] = max(tree[2 * u + 1], tree[2 * u + 2]);
}

void solve (int y, int x){
    assert(y < x);
    
    // Query outside of known range
    int fst = (year2int.begin())->first;
    int lst = (--year2int.end())->first;
    if (x < fst or y > lst){
        puts("maybe");
        return;
    }
        
    map <int, int> :: iterator lb, ub, p, q;
    lb = year2int.lower_bound(y);
    ub = --year2int.upper_bound(x);
        
    // No element in the query is in known
    if(lb->first > ub->first){
        puts("maybe");
        return;
    }
    
    // All values are known
    if (lb->first == y and ub->first == x and ub->second - lb->second == x - y){
        x = year2int[x]; y = year2int[y];
        if (a[y] < a[x]) {
            puts("false");
            return;
        }
        int ans = -1;
        if (y + 1 <= x - 1) ans = query(0, 0, n - 1, y + 1, x - 1);
        if (a[x] > ans) puts("true");
        else puts("false");
        return;
    }
    
    // Some values are not known
    
    p = year2int.lower_bound(y + 1);
    q = year2int.upper_bound(x - 1);
    int ans = 0;
    if (y + 1 <= x - 1 and p != year2int.end() and q != year2int.begin() and p->first <= (--q)->first){
        // printf("Pregunto por los años: %d, %d\n", p->first, q->first);
        ans = query(0, 0, n - 1, p->second, q->second);
    }
    
    // both y and x are known
    if (lb->first == y and ub->first == x){
        //printf("Para y = %d, x = %d entre a x y y conocidos\n", y, x);
        if (ans < a[year2int[x]] and a[year2int[x]] <= a[year2int[y]]) puts("maybe");
        else puts("false");
        return;
    }
    // y known but not x
    if (lb->first == y){
        // printf("Para y = %d, x = %d entre a y conocido\n", y, x);
        if (ans < a[year2int[y]] ) puts("maybe");
        else puts("false");
        return;
    }
    // x known but not y
    if (ub->first == x){
        // printf("Para y = %d, x = %d entre a x conocido\n", y, x);
        if (ans < a[year2int[x]]) puts("maybe");
        else puts("false");
    }
    
    // Neither x nor y known
    puts("maybe");
    
}


int main(){
    assert(MAXN <= MAXTREE);
    bool first = true;
    while (scanf("%d", &n) == 1){
        year2int.clear();
        for (int i = 0; i < n; i++){
            int y, r; scanf("%d %d", &y, &r);
            year2int[y] = i;
            a[i] = r;
        }
        
        int m; scanf("%d", &m);
        if (n == 0 and m == 0) break;
        
        build(0, 0, n - 1);
        if (!first) puts("");
        
        map <int, int> :: iterator it;
        
        // puts("\nMap has:");
        // for (it = year2int.begin(); it != year2int.end(); it++){
        //     printf("%d->%d\n", it->first, it->second);
        // }
        
        for (int i = 0; i < m; i++){
            int y, x; scanf("%d %d", &y, &x);
            solve(y, x);
        }  
        first = false;
    }
        
    return 0;
}