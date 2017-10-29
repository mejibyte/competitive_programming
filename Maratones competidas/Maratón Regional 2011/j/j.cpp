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

class SegmentTree {
    public:
        vector<long long> arr, tree;
        int n;
        
        SegmentTree(){}
        SegmentTree(const vector <long long> &arr) : arr(arr) {
            initialize();
        }
        
        void initialize() {
            n = arr.size();
            tree.resize(4 * n + 1);
            initialize(0, 1, n - 1);
        }
        
        long long query(int query_left, int query_right) const {
            return query(0, 1, n - 1, query_left, query_right);
        }
        
        void update(int where, long long what) {
            update(0, 1, n - 1, where, what);
        }
        
                void print(int node, int node_left, int node_right);
        
    private:
        long long initialize(int node, int node_left, int node_right);    
        long long query(int node, int node_left, int node_right, int query_left, int query_right) const;
        void update(int node, int node_left, int node_right, int where, long long what);
};

long long SegmentTree::initialize(int node, int node_left, int node_right) {
    if (node_left == node_right) {
        tree[node] = arr[node_left] % mod;
        //printf("node (id=%d, [%d, %d] has %d\n", node, node_left, node_right, tree[node]);        
        return tree[node];
    }
    
    int half = (node_left + node_right) / 2;
    long long ans_left = initialize(2 * node + 1, node_left, half);
    long long ans_right = initialize(2 * node + 2, half + 1, node_right);
    
    long long ans =  bigmod(B, node_right - half) * ans_left + ans_right;
    ans %= mod;
    tree[node] = ans;
    //printf("node (id=%d, [%d, %d] has %d\n", node, node_left, node_right, ans);
    return tree[node];
}


void SegmentTree::print(int node, int node_left, int node_right) {
    if (node_left == node_right) {
        tree[node] = arr[node_left] % mod;
        dprintf("node (id=%d, [%d, %d] has %lld\n", node, node_left, node_right, tree[node]);        
        return;
    }
    dprintf("node (id=%d, [%d, %d] has %lld\n", node, node_left, node_right, tree[node]);
    int half = (node_left + node_right) / 2;
    print(2 * node + 1, node_left, half);
    print(2 * node + 2, half + 1, node_right);    
    
}

long long SegmentTree::query(int node, int node_left, int node_right, int query_left, int query_right) const {
    //printf("Node is (%d, [%d, %d]), query is (%d, %d)\n", node, node_left, node_right, query_left, query_right);
    if (node_right < query_left || query_right < node_left) return 0;
    if (query_left == node_left && node_right == query_right) {
        dprintf("Query is the same as node (id=%d, [%d, %d]). Returning %lld\n", node, node_left, node_right, tree[node]);
        return tree[node];
    }
    
    if (node_left == node_right) {
        return tree[node];    
    }
    
    int half = (node_left + node_right) / 2;
    
    long long ans_left = query(2 * node + 1, node_left, half, query_left, query_right);
    long long ans_right = query(2 * node + 2, half + 1, node_right, query_left, query_right);
     
    int limit = min(query_right, node_right);
    
    long long ans = bigmod(B, limit - half) * ans_left + ans_right;
    ans %= mod;
    
    dprintf("B = %lld, query_right = %d, half = %d, query_right - half = %d\n", B, query_right, half, query_right - half);
    dprintf("query on node(id=%d, [%d, %d]). Query is (%d, %d). left is %lld, right is %lld, factor is %lld, ans = %lld\n", node, node_left, node_right, query_left, query_right, ans_left, ans_right, bigmod(B, limit - half), ans);
    return ans;
}


void SegmentTree::update(int node, int node_left, int node_right, int where, long long what) {
    if (where < node_left || node_right < where) return;
    if (node_left == where && where == node_right) {
        arr[where] = what;
        tree[node] = what;
        dprintf("Update leaf (id=%d, [%d, %d]). Here = %lld\n", node, node_left, node_right,tree[node]);
        return;
    }
    
    int half = (node_left + node_right) / 2;
    if (where <= half) {
        update(2 * node + 1, node_left, half, where, what);
    } else {
        update(2 * node + 2, half + 1, node_right, where, what);
    }
   
    
    long long ans_left = tree[2 * node + 1];
    long long ans_right = tree[2 * node + 2];
   
    long long ans = bigmod(B, node_right - half) * ans_left + ans_right;
    ans %= mod;
    tree[node] = ans;
    
    dprintf("Update node (id=%d, [%d, %d]). Left = %d, right = %d\n", node, node_left, node_right, ans_left, ans_right);
}


int main() {

    long long b, p, l, n, n_input;

    while(cin >> b >> p >> l >> n) {
        if(b == 0 and p == 0 and l == 0 and n == 0) break;
        B = b;
        mod = p;
        
        n_input = n;
        
        vector<long long> f(l + 1, 0);
        SegmentTree tree(f);
        
        char cm;
        long long i, v; 
        while(n_input--) {
            cin >> cm >> i >> v;
            // responder al comando cm, i, v 
            if (cm == 'E') {
                tree.update(i, v);
            } else if (cm == 'H'){
                long long ans = tree.query(i, v);
                cout << ans << endl;
                
            } 
        }
        puts("-");
    }
    return 0;
}
