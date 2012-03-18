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

#include <bitset>

const int MAXL = 2000 * 100 + 5;
int tree[26][MAXL];
bitset<MAXL> deleted;

void add(int * tree, int where, int what) {
    for (where++; where < MAXL; where += where & -where) {
        tree[where] += what;
    }
}

int get(int * tree, int where) {
    int ans = 0;
    for (where++; where > 0; where -= where & -where) {
        ans += tree[where];
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    
    int k; cin >> k;
    string t; cin >> t;
    string s = "";
    for (int i = 0; i < k; ++i) s += t;
    int n = s.size();
    
    for (int i = 0; i < s.size(); ++i) {
        add(tree[s[i] - 'a'], i, +1);
    }
    
    int q; cin >> q;
    for (int removed = 0; removed < q; ++removed) {
        int pos; char c; cin >> pos >> c;
        c -= 'a';
        
        int low = 0, high = n - removed + 1;
        while (low < high) {
            int m = (low + high) >> 1;
            int sum = get(tree[c], m);
            if (sum < pos) low = m + 1;
            else high = m;
        }
        assert(get(tree[c], low) == pos);
        deleted[low] = true;
        add(tree[c], low, -1);
    }
    for (int i = 0; i < n; ++i){
        if (!deleted[i]) cout << s[i];
    }
    cout << endl;
    
    return 0;
}