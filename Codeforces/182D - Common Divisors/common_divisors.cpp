// Accepted.
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

const int MAXN = 200005;
long long power[MAXN];

struct Hashy {
	string s;
	vector<long long> h;

	Hashy(const string &t) : s(t) {
		h.resize(s.size());
		assert(s.size() > 0);
		h[0] = s[0];
		for (int i = 1; i < s.size(); ++i) {
			h[i] = h[i - 1] * 33 + s[i];
		}		
	}

	long long hash(int i, int j) const {
		long long ans = h[j];
		if (i - 1 >= 0) ans -= h[i - 1] * power[j - i + 1];
		return ans;
	}

	int size() const {
		return s.size();
	}
};

bool is_period(const Hashy &a, int len) {
	int n = a.size() / 2;
	if (len == n) return true;
	if (n % len != 0) return false;	
	long long original = a.hash(0, n - 1);
	long long shifted = a.hash(len, len + n - 1);
	return original == shifted;
}

int main() {
	power[0] = 1;
	for (int i = 1; i < MAXN; ++i) power[i] = power[i - 1] * 33;

	string s, t;
	cin >> s >> t;
	Hashy a(s + s), b(t + t);
	int ans = 0;
	int n = min(s.size(), t.size());
	for (int len = 1; len <= n; ++len) {
		if (is_period(a, len) and is_period(b, len) and a.hash(0, len - 1) == b.hash(0, len - 1)) ans++;
	}
	cout << ans << endl;
	return 0;
}