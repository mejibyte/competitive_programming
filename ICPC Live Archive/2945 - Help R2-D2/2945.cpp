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

struct Node {
  int y, payload, max;
  Node *l, *r;
  Node(int k) : payload(k), max(k), y(rand()), l(null), r(null) { }
  Node() : payload(0), max(0), y(rand()) , l(null), r(null) { }
};

Node* update(Node* p) {
  if (p) {
    p->max = p->payload;
    if (p->l and p->l->max > p->max) {
        p->max = p->l->max;
    }
    if (p->r and p->r->max > p->max) {
        p->max = p->r->max;
    }
  }
  return p;
}

Node* merge(Node* l, Node *r) {
  if (l == null) return update(r);
  if (r == null) return update(l);
  
  if (l->y > r->y) {
    l->r = merge(l->r, r);
    return update(l);
  } else {
    r->l = merge(l, r->l);
    return update(r);
  }
}

void print(Node *p) {
  if (p == null) return;
  print(p->l);
  printf("payload = %d, y = %d, max = %d\n", p->payload, p->y, p->max);
  print(p->r);
}

void traverse(Node * p) {
  if (p == null) return;
  traverse(p->l);
  printf("%d ", p->payload);
  traverse(p->r);
}

const int MAXN = 1000005;
Node nodes[MAXN];
int a[MAXN];
int C;

void insert(Node * p, int v) {
    assert(p);
    if (p->l and p->l->max >= v) {
        insert(p->l, v);
    } else if (p->payload >= v) {
        p->payload -= v;
    } else {
        insert(p->r, v);
    }
    update(p);
}

int main(){
    bool first = true;
    while (scanf("%d", &C) == 1) {
        if (first) first = false; else puts("");
        int n; scanf("%d ", &n);
        for (int i = 0; i < n; ) {
            static char line[256];
            scanf("%s ", line);
            if (line[0] == 'b') {
                int r, v; scanf("%d %d", &r, &v);
                for (int k = 0; k < r; ++k) {
                    a[i++] = v;
                }
            } else {
                int v; sscanf(line, "%d", &v);
                a[i++] = v;
            }
        }
        // for (int i = 0; i < n; ++i) printf("%d ", a[i]); puts("");
        int nodeCount = 0;
        int wasted = 0;
        Node * root = null;
        for (int i = 0; i < n; ++i) {
            // printf("Step i = %d, a[i] = %d\n", i, a[i]);
            if (root and root->max >= a[i]) {
                // printf("root is %x and max is %d\n", root, root->max);
                insert(root, a[i]);
                wasted -= a[i];
            } else {
                Node * next = &nodes[nodeCount++];
                next->l = next->r = null;
                next->y = rand();
                next->payload = next->max = C - a[i];
                wasted += C - a[i];
                root = merge(root, next);
            }
        }
        printf("%d %d\n", nodeCount, wasted);
    }
    return 0;
}
