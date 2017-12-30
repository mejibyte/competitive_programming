#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <cassert>
#include <memory>
#include <iostream>

using namespace std;

long long oo = (long long)(1e9);

#define null NULL

struct Node {
    int x, y, size;

    // min = min element in this subtree
    // max = max element in this subtree
    // min_diff = min difference between any two consecutive elements in this subtree. oo if the subtree has only 1 node.
    long long min, max, min_diff;
    Node *l, *r;
    Node(int k) : x(k), y(rand()), size(1),
                  l(null), r(null), min(k), max(k), min_diff(oo) { }
};

Node* relax(Node* p) {
    if (p) {
        p->size = 1;
        p->min = p->max = p->x;
        p->min_diff = oo;
        if (p->l) {
            p->size += p->l->size;
            p->min = min(p->min, p->l->min);
            p->max = max(p->max, p->l->max);
            p->min_diff = min(p->min_diff, p->l->min_diff);
        }
        if (p->r) {
            p->size += p->r->size;
            p->min = min(p->min, p->r->min);
            p->max = max(p->max, p->r->max);
            p->min_diff = min(p->min_diff, p->r->min_diff);
        }

        if (p->size > 1) {
            long long left, right;
            if (p->l) {
                left = p->l->max;
                right = p->x;
                p->min_diff = min(p->min_diff, left - right);
            }
            if (p->r) {
                left = p->x;
                right = p->r->min;
                p->min_diff = min(p->min_diff, left - right);
            }
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

Node* erase(Node* t, int x) {
    if (t == null) return null;
    if (t->x == x) {
        Node *q = merge(t->l, t->r);
        return relax(q);
    } else {
        if (x < t->x) t->l = erase(t->l, x);
        else t->r = erase(t->r, x);
        return relax(t);
    }
}

// Returns any node with the given x.
Node* find(Node* cur, int x) {
    while (cur != null and cur->x != x) {
        if (x < cur->x) cur = cur->l;
        else cur = cur->r;
    }
    return cur;
}

void print(Node* cur) {
    if (cur == null) return;
    print(cur->l);
    cout << cur->x << " ";
    print(cur->r);
}

void solve() {
    int n;
    long long d;
    cin >> n >> d;

    vector<Node*> nodes;
    Node* root = nullptr;


    vector<int> diffs;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;

        nodes.push_back(new Node(x));
        root = insert(root, nodes.back());

        long long ans = d;
        if (root->size == 1) {
            ans = 0;
        } else if (root->size == 2) {
            ans = max(d - root->max + root->min, 0LL);
        } else {
            long long a = root->min, b = root->max;

            root = erase(root, a);
            root = erase(root, b);

            Node* left, *middle, *right, *tmp;
            split(root, b-d, left, tmp);
            split(tmp, a+d-1, middle, right);


            if (middle == null) {
                ans = 0LL;
            } else {
                assert(middle->size >= 1);
                ans = min(ans, max(a + d - middle->min, 0LL));
                ans = min(ans, max(middle->max - b + d, 0LL));

                long long option = a-b+d+d + middle->min_diff;
                diffs.push_back(middle->min_diff);
                ans = min(ans, option);

                //cout << "middle: "; print(middle); cout << endl;
                //printf("mid.min=%lld, mid.max=%lld, mid.min_diff=%lld\n", middle->min, middle->max, middle->min_diff);

            }

            root = merge(left, merge(middle, right));

            // Insert a and b again.
            nodes.push_back(new Node(a));
            root = insert(root, nodes.back());
            nodes.push_back(new Node(b));
            root = insert(root, nodes.back());
        }

        if (i > 0) cout << " ";
        cout << (ans < 0 ? 0 : ans);
    }
    //cout << " (diffs: "; for (auto x : diffs) cout << x << " "; cout << ")";
    cout << endl;


    for (auto p : nodes) {
        delete p;
    }
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    srand(124);
    int cases;
    cin >> cases;
    while (cases--) solve();
    return 0;
}
