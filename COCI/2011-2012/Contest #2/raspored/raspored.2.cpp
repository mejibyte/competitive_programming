#include <iostream>
#include <cstdlib>
using namespace std;

#define null NULL

const int MAXN = 200005;

int L[MAXN];
int T[MAXN];

struct Node {
    int x, y, size;
    long long sum, hash;
    Node * l, * r;
    
    Node(int _x){
        l = r = null;
        sum = hash = size = 0;
        x = _x;
        y = rand();
    }
};

Node * update(Node * u) {
    if (u == null) return u;
    u->size = 1;
    u->sum = u->x;

    int k = u->r ? u->r->size : 0;
    u->hash = 1LL * (k + 1) * u->x;
    if (u->l) {
        u->size += u->l->size;
        u->sum += u->l->sum;
        u->hash += 1LL * (k + 1) * u->l->sum + u->l->hash;
    }
    if (u->r) {
        u->size += u->r->size;
        u->sum += u->r->sum;
        u->hash += u->r->hash;
    }
    return u;
}

void split(Node * where, int by, Node* &l, Node* &r) {
    if (where == null) {
        l = r = null;
    } else {
        if (where->x > by) {
            r = where;
            split(where->l, by, l, r->l);
        } else {
            l = where;
            split(where->r, by, l->r, r);
        }
        update(l); update(r);
    }
}

Node * insert(Node * where, Node * what) {
    if (where == null or what->y > where->y) {
        split(where, what->x, what->l, what->r);
        return update(what);
    } else {
        if (what->x < where->x) { // insertar a la izquierda
            where->l = insert(where->l, what);
            return update(where);
        } else { // insertar a la derecha
            where->r = insert(where->r, what);
            return update(where);
        }
    }
}

Node * merge(Node * a, Node * b) {
    if (a == null) return update(b);
    if (b == null) return update(a);
    
    if (a->y > b->y) { // a arriba
        a->r = merge(a->r, b);
        return update(a);
    } else { // b arriba
        b->l = merge(a, b->l);
        return update(b);
    }
}

Node * erase(Node * where, int what) {
    if (where == null) return where;
    if (where->x == what) { // got it
        Node * q = merge(where->l, where->r);
        delete where;
        return update(q);
    } else if (what < where->x) {
        where->l = erase(where->l, what);
        return update(where);
    } else {
        where->r = erase(where->r, what);
        return update(where);        
    }
}


void print(Node * where, int depth) {
    if (where == null) return;
    
    for (int i = 0; i < depth; ++i) printf("  ");
    printf("(x = %d, y = %d, sum = %d, hash = %d, size = %d)\n", where->x,where->y,(int)where->sum,(int)where->hash,where->size);
    for (int i = 0; i < depth; ++i) printf("  ");printf("left:\n"); 
    print(where->l, depth + 1); 
    for (int i = 0; i < depth; ++i) printf("  ");printf("right:\n");
    print(where->r, depth + 1);
}

int main() {
    ios::sync_with_stdio(false);
    
    //cout << sizeof(Node) << endl;
    
    srand(777);
    
    int n, C;
    cin >> n >> C;
    
    Node * root = null;

    long long constant = 0;    
    for (int i = 0; i < n; ++i) {
        cin >> L[i] >> T[i];
        constant += L[i];
        
        root = insert(root, new Node(T[i]));
    }
    
    //print(root, 0);
    
    cout << constant - root->hash << endl;
    
    while (C--) {
        int who, nl, nt;
        cin >> who >> nl >> nt;
        who--;
        // erase T[who] and insert nt
        root = erase(root, T[who]);
        root = insert(root, new Node(nt));
        
        constant -= L[who];
        constant += nl;
        
        cout << constant - root->hash << endl;
        
        L[who] = nl;
        T[who] = nt;
    }
    return 0;
}
