#define _CRT_SECURE_NO_DEPRECATE
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <numeric>
#include <cctype>
#include <climits>
using namespace std;

typedef long long int64; 
typedef unsigned long long uint64;

template<typename T> int size(const T& c) { return int(c.size()); }
template<typename T> T abs(T x) { return x < 0 ? -x : x; }
template<typename T> T sqr(T x) { return x*x; }
template<typename T> bool remin(T& x, T y) { if (x <= y) return false; x = y; return true; }
template<typename T> bool remax(T& x, T y) { if (x >= y) return false; x = y; return true; }

#define FOR(i, a, b) for (int i(a), _b(b); i <= _b; ++i)
#define FORD(i, a, b) for (int i(a), _b(b); i >= _b; --i)
#define REP(i, n) for (int i(0), _n(n); i < _n; ++i)
#define REPD(i, n) for (int i((n) - 1); i >= 0; --i)

const int maxn = 100+5;
int memo[maxn][257];
int D, I, M, n;
int a[maxn];

int numInserts(int x) {
	if (x%M == 0) return max(0, x/M-1);
	return x/M;
}

int solve(int at, int prev) {
	if (at == n) return 0;
	int& res = memo[at][prev];
	if (res != -1) return res;
	res = D+solve(at+1, prev);
	REP(i, 256) {
		int cur = abs(a[at]-i);
		if (prev != 256) cur += I*numInserts(abs(prev-i));
		cur += solve(at+1, i);
		remin(res, cur);
	}
	return res;
}

int allSame(int c) {
	int res = 0;
	REP(i, n) if (a[i] != c)
		res += min(D, abs(a[i]-c));
	return res;
}

int main() {

	int ntests;
	scanf("%d", &ntests);
	FOR(test, 1, ntests) {
		printf("Case #%d: ", test);
		scanf("%d%d%d%d", &D, &I, &M, &n);
		REP(i, n) scanf("%d", &a[i]);
		if (M == 0) {
			int res = INT_MAX;
			REP(i, 256) remin(res, allSame(i));
			printf("%d\n", res);
		} else {
			memset(memo, -1, sizeof(memo));
			printf("%d\n", solve(0, 256));
		}
	}
}
