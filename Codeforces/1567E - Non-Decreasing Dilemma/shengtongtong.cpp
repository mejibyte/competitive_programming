// https://codeforces.com/contest/1567/submission/127956967
#include <bits/stdc++.h>

#include <chrono>
using namespace std::chrono;

using namespace std;

const int maxN = 222222;
int n, q, a[maxN];
struct info {
	int l, r, fl, fr, sz;
	long long tot;
} d[maxN * 4];

info operator + (info a, info b) {
	info c;
	c.l = a.l;
	c.r = b.r;
	c.sz = a.sz + b.sz;
	c.fl = (a.fl == a.sz && a.r <= b.l) ? (a.fl + b.fl) : a.fl;
	c.fr = (b.fr == b.sz && a.r <= b.l) ? (b.fr + a.fr) : b.fr;
	c.tot = a.tot + b.tot + ((a.r <= b.l) ? (1ll * a.fr * b.fl) : 0);
	return c;
}

void bd(int k, int l, int r) {
	if (l == r) {
		d[k] = (info) {a[l], a[l], 1, 1, 1, 1ll};
	} else {
		int mid = (l + r) / 2;
		bd(k * 2, l, mid);
		bd(k * 2 + 1, mid + 1, r);
		d[k] = d[k * 2] + d[k * 2 + 1];
	}
}

void mdf(int k, int l, int r, int x) {
	if (l == r) {
		d[k] = (info) {a[l], a[l], 1, 1, 1, 1ll};
	} else {
		int mid = (l + r) / 2;
		if (x <= mid) mdf(k * 2, l, mid, x);
		else mdf(k * 2 + 1, mid + 1, r, x);
		d[k] = d[k * 2] + d[k * 2 + 1];
	}
}

info qry(int k, int l, int r, int x, int y) {
	if (l == x && r == y) {
		return d[k];
	} else {
		int mid = (l + r) / 2;
		if (y <= mid) return qry(k * 2, l, mid, x, y);
		else if (x > mid) return qry(k * 2 + 1, mid + 1, r, x, y);
		else return qry(k * 2, l, mid, x, mid) + qry(k * 2 + 1, mid + 1, r, mid + 1, y);
	}
}

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

  auto start = high_resolution_clock::now();
	bd(1, 1, n);
  auto elapsed = duration_cast<microseconds>(high_resolution_clock::now() - start);
  cerr << "initialize took " << elapsed.count() << "us" << endl;

  long long total_update_usec = 0;
  long long total_query_usec = 0;

	for (int i = 0; i < q; i++) {
		int t, x, y;
		scanf("%d%d%d", &t, &x, &y);
		if (t == 1) {
			a[x] = y;
      auto start = high_resolution_clock::now();
      mdf(1, 1, n, x);
      auto elapsed = duration_cast<microseconds>(high_resolution_clock::now() - start);
      total_update_usec += elapsed.count();
		} else {
      auto start = high_resolution_clock::now();
      auto ans = qry(1, 1, n, x, y);
      auto elapsed = duration_cast<microseconds>(high_resolution_clock::now() - start);
      total_query_usec += elapsed.count();
			printf("%lld\n", ans.tot);
		}
	}

  cerr << "total_update_usec: " << total_update_usec << endl;
  cerr << "total_query_usec: " << total_query_usec << endl;
}