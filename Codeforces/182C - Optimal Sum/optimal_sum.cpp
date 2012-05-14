// Accepted.

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int MAXN = 100005;

int a[MAXN];

#define null NULL

// treap
struct Node {
	int x, y, size;
	long long sum;
	Node *l, *r;

	Node(int value) : x(value), l(null), r(null), y(rand()), size(1), sum(x) {}
};

Node* update(Node* u) {
	if (u) {
		u->size = 1;
		u->sum = u->x;
		if (u->l) u->size += u->l->size, u->sum += u->l->sum;
		if (u->r) u->size += u->r->size, u->sum += u->r->sum;
	}
	return u;
}

void split(Node* u, int x, Node* &l, Node* &r) {
	if (u == null) {
		l = r = null;
		return;
	}
	if (u->x <= x) {
		l = u;
		split(u->r, x, u->r, r);
	} else {
		r = u;
		split(u->l, x, l, u->l);
	}
	update(l);
	update(r);
}

Node* merge(Node *a, Node *b) {
	if (a == null) return update(b);
	if (b == null) return update(a);
	if (a->y > b->y) {
		a->r = merge(a->r, b);	
		return update(a);
	} else {
		b->l = merge(a, b->l);
		return update(b);
	}
}

Node* insert(Node* u, Node* what) {
	if (u == null or what->y > u->y) {
		split(u, what->x, what->l, what->r);
		return update(what);
	}
	if (what->x < u->x) u->l = insert(u->l, what);
	else u->r = insert(u->r, what);
	return update(u);
}

Node* erase(Node* u, int what) {
	if (u == null) return u;
	if (u->x == what) {
		Node* p = merge(u->l, u->r);
		delete u;
		return update(p);
	}
	if (what < u->x) u->l = erase(u->l, what);
	else u->r = erase(u->r, what);
	return update(u);
}

long long biggest(Node *u, int k) {
	if (u == null or k == 0) return 0;

	if (u->size <= k) return u->sum;	

	int right = u->r ? u->r->size : 0;
	if (right > k) return biggest(u->r, k);

	long long ans = biggest(u->r, k);
	k -= right;
	if (k > 0) {
		ans += u->x;
		k--;
	}
	if (k > 0) ans += biggest(u->l, k);
	return ans;
}

void print(Node *u) {
	if (u == null) { return; }
	print(u->l); printf("%d ", u->x); print(u->r);
}

int main() {
	int n, len;
	cin >> n >> len;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}	
	int k; cin >> k;

	Node *positive = null, *negative = null;

	long long sum = 0, best = 0;

	for (int i = 0; i < len; ++i) {
		if (a[i] > 0) positive = insert(positive, new Node(a[i]));
		else negative = insert(negative, new Node(-a[i]));

		sum += a[i];
		//printf("inserted %d\n", a[i]);
	}

	for (int i = 0; i + len <= n; ++i) {

		//puts("");
		//printf("i = %d, sum = %lld\n", i, sum);

		//printf("positive: "); print(positive); puts("");
		//printf("negative: "); print(negative); puts("");
		//printf("negative root sum: %lld\n", negative ? negative->sum : 0LL);

		//printf("biggest k positive = %lld\n", biggest(positive, k));
		//printf("biggest k negative = %lld\n", biggest(negative, k));

		//printf("abs(sum - 2 * biggest(positive, k)) = %lld\n", abs(sum - 2 * biggest(positive, k)));
		//printf("abs(sum + 2 * biggest(negative, k)) = %lld\n", abs(sum + 2 * biggest(negative, k)));

		best = max(best, abs(sum - 2 * biggest(positive, k)));
		best = max(best, abs(sum + 2 * biggest(negative, k)));

		// remove i
		sum -= a[i];
		if (a[i] > 0) positive = erase(positive, a[i]);
		else negative = erase(negative, -a[i]);

		//printf("removed %d\n", a[i]);

		// add i + len
		if (i + len < n) {
			sum += a[i + len];
			if (a[i + len] > 0) positive = insert(positive, new Node(a[i + len]));
			else negative = insert(negative, new Node(-a[i + len]));

			//printf("added %d\n", a[i + len]);
		}	
	}
	cout << best << endl;
	return 0;
}