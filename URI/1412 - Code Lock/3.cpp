// Based on https://github.com/gustavosm/uri/blob/master/1412.cpp, but simplified a little bit by me.
// Accepted
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <iostream>

using namespace std;

int main() {
	string s;
	while (getline(cin, s))	{
		if (s == "*") return 0;
		string aux;
		aux.push_back('a');
		aux += s;
		aux.push_back('a');

		int n = aux.size();

		vector<int> v;
		for (int i = 1; i < n; ++i)	{
			int a = (int)(aux[i] - aux[i - 1] + 26);
			v.push_back(a % 26);
		}
		sort(v.begin(), v.end());
		assert(accumulate(v.begin(), v.end(), 0) % 26 == 0);

		int ans = 0;
		int left = 0, right = v.size() - 1;
		while (left <= right) {
			if (v[left] == 0) {
				left++;
				continue;
			}
			if (v[right] == 0) {
				right--;
				continue;
			}

			assert(left < right); // If we are going to decrement one and decrement the other, they must be different.

			ans++;
			v[left] = (v[left] - 1 + 26) % 26;
			v[right] = (v[right] + 1) % 26;
		}
		cout << ans << '\n';
	}
}
