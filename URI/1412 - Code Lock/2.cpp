// Based on https://github.com/gustavosm/uri/blob/master/1412.cpp, but simplified by me.
// Accepted
#include <string>
#include <vector>
#include <algorithm>
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

		int ans = 0;
		int pos1 = 0;
		while (pos1 < v.size() && v[pos1] == 0) {
			++pos1;
		}

		if (pos1 == v.size()) {
			cout << "0\n";
			continue;
		}
		int pos2 = v.size() - 1;
		while (pos2 >= 0)
		{
			++ans;
			v[pos1] = (v[pos1] - 1) % 26;
			v[pos2] = (v[pos2] + 1) % 26;
			while (pos1 < v.size() && v[pos1] == 0) ++pos1;
			if (pos1 == v.size()) break;
			while (pos2 >= 0 && v[pos2] == 0) --pos2;
		}
		cout << ans << '\n';
	}
}
