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

#define null NULL

const int MAXN = 100005;

enum { Bus, Person };

struct Event {
    int l, r, t, index, type;
    void read() {
        cin >> l >> r >> t;
    }
    bool operator < (const Event &other) const {
        if (l != other.l) return l < other.l;
        return type < other.type; // buses first
    }
} events[2 * MAXN];


#define null NULL

struct Node {
    int x, y, value, maxValue, index, size;
    Node *l, *r;
    Node(int x, int value, int index) : x(x), y(rand()), value(value), maxValue(value), index(index), l(null), r(null), size(1) { }
};

Node* relax(Node* p) {
    if (p) {
        p->maxValue = p->value;
        p->size = 1;
        if (p->l) {
            p->maxValue = max(p->maxValue, p->l->maxValue);
            p->size += p->l->size;
        }
        if (p->r) {
            p->maxValue = max(p->maxValue, p->r->maxValue);
            p->size += p->r->size;
        }
    }
    return p;
}

void split(Node* t, int x, Node* &l, Node* &r) {
    if (t == null) l = r = null; else {
        if (x < t->x) {
            split(t->l, x, l, t->l);
            r = relax(t);
        } else {
            split(t->r, x, t->r, r);
            l = relax(t);
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

Node* erase(Node* t, int x) {
    if (t == null) return null;
    if (t->x == x) {
        Node *q = merge(t->l, t->r);
        delete t;
        return relax(q);
    } else {
        if (x < t->x) t->l = erase(t->l, x);
        else t->r = erase(t->r, x);
        return relax(t);
    }
}

// struct Node {
//     int x, y, value, maxValue, index;
//     Node * l, * r;
//     
//     Node(int _x, int _value, int _index) {
//         x = _x;
//         y = rand();
//         value = _value;
//         index = _index;
//         maxValue = value;
//     }
// };
// 
// Node * update(Node * t) {
//     assert(t);
//     t->maxValue = t->value;
//     if (t->l and t->l->maxValue > t->maxValue) t->maxValue = t->l->maxValue;
//     if (t->r and t->r->maxValue > t->maxValue) t->maxValue = t->r->maxValue;
//     return t;
// }
// 
// void split(Node * t, int x, Node *&L, Node *&R) {
//     if (t == null) {
//         L = R = null;
//     } else {
//         if (t->x <= x) {
//             split(t->r, x, t->r, R);
//             L = update(t);
//         } else {
//             split(t->l, x, L, t->l);
//             R = update(t);
//         }
//     }
// }
// 
// Node * merge(Node * l, Node * r) {
//     if (l == null) return update(r);
//     if (r == null) return update(l);
//     if (l->y > r->y) {
//         l->r = merge(l->r, r);
//         return update(l);
//     } else {
//         r->l = merge(l, r->l);
//         return update(r);
//     }
// }
// 
// Node * insert(Node * u, Node * what) {
//     if (u == null || what->y > u->y) {
//         split(u, what->x, what->l, what->r);
//         return update(what);
//     } else {
//         if (what->x < u->x) {
//             u->l = insert(u->l, what);
//         } else {
//             u->r = insert(u->r, what);
//         }
//         return update(u);
//     }
// }
// 
void print(Node *p, int depth = 0) {
    if (p == null) return;
    print(p->l, depth + 2);
    for (int i = 0; i < depth; ++i) printf(" ");
    printf("x = %d, y = %d, v = %d, mV = %d, i = %d, size = %d\n", p->x, p->y, p->value, p->maxValue, p->index, p->size);
    print(p->r, depth + 2);
}

int findAns(Node *u, int value) {
    if (u == null || u->maxValue < value) return -1;
    if (u->l and u->l->maxValue >= value) return findAns(u->l, value);
    if (u->value >= value) return u->index + 1; // no puede haber uno mejor
    return findAns(u->r, value);
    
    
}

int main(){
    srand(7);
    //ios::sync_with_stdio(false);
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; ++i) events[i].read(), events[i].index = i, events[i].type = Bus;
    for (int i = 0; i < m; ++i) {
        events[i + n].read(), events[i + n].index = i, events[i + n].type = Person;
    }
    
    static int ans[MAXN];
    
    sort(events, events + n + m);
    
    // for (int i = 0; i < n + m; ++i) {
    //     printf("%d %d %d %d\n", events[i].l, events[i].r, events[i].t, events[i].type);
    // }
    
    Node * root = null;
    
    for (int i = 0; i < n + m; ++i) {
        const Event &e = events[i];
        if (e.type == Bus) {
            Node * next = new Node(e.t, e.r, e.index);
            root = insert(root, next);
            // printf("Inserted bus %d, %d, %d, %d\n", e.l, e.r, e.t, e.index);
            // print(root);
        } else {
            Node * l, * r;
            split(root, e.t - 1, l, r);
            ans[e.index] = findAns(r, e.r);
            
            root = merge(l, r);
        }
    }
    for (int i = 0; i < m; ++i) cout << ans[i] << " "; cout << endl;
    
    
    return 0;
}