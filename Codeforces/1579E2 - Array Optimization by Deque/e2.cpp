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
#include <bitset>
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
using namespace std;

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cerr << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

#define null NULL

struct Node {
    int x, y, size;
    Node *l, *r;
    Node(int k) : x(k), y(rand()), size(1),
                  l(null), r(null) { }
    Node() : Node(0) {}
};

Node* relax(Node* p) {
    if (p) {
        p->size = 1;
        if (p->l) {
            p->size += p->l->size;
        }
        if (p->r) {
            p->size += p->r->size;
        }
    }
    return p;
}

// Puts all elements <= x in l and all elements > x in r.
void split(Node* t, int x, Node* &l, Node* &r) {
    if (t == null) l = r = null; else {
        if (t->x <= x) {
            split(t->r, x, t->r, r);
            l = relax(t);
        } else {
            split(t->l, x, l, t->l);
            r = relax(t);
        }
    }
}

Node* merge(Node* l, Node *r) {
    if (l == null) return relax(r);
    if (r == null) return relax(l);
    if (l->y > r->y) {
        l->r = merge(l->r, r);
        return relax(l);
    } else {
        r->l = merge(l, r->l);
        return relax(r);
    }
}

Node* insert(Node* t, Node* m) {
    if (t == null || m->y > t->y) {
        split(t, m->x, m->l, m->r);
        return relax(m);
    }
    if (m->x < t->x) t->l = insert(t->l, m);
    else t->r = insert(t->r, m);
    return relax(t);
}

const int MAXN = 20005;
Node nodes[MAXN];

void solve() {
    int n;
    cin >> n;
    long long answer = 0;

    Node* root = NULL;

    for (int i = 0; i < n; ++i) {
        int next;
        cin >> next;
        nodes[i] = Node(next);

        Node *l, *r;
        split(root, next - 1, l, r);
        long long option1 = (l ? l->size : 0);
        root = merge(l, r);

        split(root, next, l, r);
        long long option2 = (r ? r->size : 0);
        root = merge(l, r);

        answer += min(option1, option2);

        root = insert(root, &nodes[i]);
    }
    cout << answer << endl;

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
