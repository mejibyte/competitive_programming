#define _CRT_SECURE_NO_DEPRECATE
#define _SECURE_SCL 0

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <cctype>
#include <sstream>
#include <cassert>
#include <bitset>
#include <memory.h>
#include <complex>

using namespace std;

#pragma comment(linker, "/STACK:200000000")

typedef long long int64;

#define forn(i, n) for(int i = 0; i < (int)(n); i++)
#define ford(i, n) for(int i = (int)(n) - 1; i >= 0; i--)
#define fore(i, a, n) for(int i = (int)(a); i < (int)(n); i++)
#define pb push_back
#define mp make_pair
#define fs first
#define sc second
#define last(a) (int(a.size()) - 1)
#define all(a) a.begin(), a.end()

const double EPS = 1E-9;
const int INF = 1000000000;
const int64 INF64 = (int64) 1E18;
const double PI = 3.1415926535897932384626433832795;

const int NMAX = (1 << 20) + 100500;
const int MOD = INF + 7;

int a[NMAX], n, m, full, s[NMAX][22], b[NMAX];
vector<vector<int> > z;
char str[110000];

void read() {
	scanf("%d%d\n", &n, &m);
	forn(i, n) {
		a[i] = 0;
		gets(str);
		int sz = (int)strlen(str);
		int val = 0;
		int p = 0;
		while ('0' <= str[p] && str[p] <= '9')
			p++;

		for (; p <= sz; p++) 
			if ('0' <= str[p] && str[p] <= '9')
				val = val * 10 + str[p] - '0';
			else
			if (val) {
				a[i] |= 1 << (val - 1);
				val = 0;
			}
	}
}

void gen() {
	n = 1000000;
	m = 20;
	forn(i, n)
		a[i] = abs(rand() * RAND_MAX + rand()) % (1 << m);
}

void print() {
	printf("%d %d\n", n, m);
	forn(i, n) {
		int cnt = 0;
		forn(j, m)
			if (a[i] & (1 << j))
				cnt++;
		printf("%d", cnt);
		forn(j, m)
			if (a[i] & (1 << j))
				printf(" %d", j + 1);
		puts("");
	}
}

int rec(int p, int msk) {
	if (p == n)
		return msk == full;

	if (z[p][msk] != -1)
		return z[p][msk];

	z[p][msk] = rec(p + 1, msk) + rec(p + 1, msk | a[p]);
	if (z[p][msk] >= MOD)
		z[p][msk] -= MOD;
	return z[p][msk];
}

int tupo() {
	full = (1 << m) - 1;
	z.assign(n, vector<int> (1 << m, -1));
	return rec(0, 0);
}

int solve() {
	full = (1 << m) - 1;
	forn(i, 1 << m)
		b[i] = 1;
	forn(i, n) {
		int na = full ^ a[i];
		b[na] *= 2;
		if (b[na] >= MOD)
			b[na] -= MOD;
	}

	ford(msk, 1 << m) {
		s[msk][m] = b[msk];
		ford(g, m) {
			s[msk][g] = s[msk][g + 1];
			if ((msk & (1 << g)) == 0)
				s[msk][g] = int(int64(s[msk][g]) * s[msk ^ (1 << g)][g] % MOD);
		}
//			for (int nmsk = (msk + 1) | msk; nmsk <= full; nmsk = (nmsk + 1) | msk)
//				s[msk] = int(int64(s[msk]) * b[nmsk] % MOD);
	}

	int res = 0;
	forn(msk, 1 << m) {
		int cof = s[msk][0];
		forn(i, m)
			if (msk & (1 << i))
				cof = -cof;

		res += cof;
		if (res >= MOD)
			res -= MOD;
		if (res < 0)
			res += MOD;
	}

	return res;
}

int main() {
#ifdef RADs_project
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

	read();
	cout << solve() << endl;
//	cerr << clock() << endl;

	return 0;

	gen();
	cout << solve() << endl;
	cerr << clock() << endl;

	return 0;

	int tt = 0;
	while (true) {
		tt++;
		gen();
		int ans1 = tupo();
		int ans2 = solve();
		cerr << tt << ' ' << ans1 << ' ' << ans2 << endl;
		if (ans1 != ans2) {
			print();
			break;
		}
	}
	
	return 0;
}