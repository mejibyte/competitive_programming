// Stolen from https://github.com/gustavosm/uri/blob/master/1412.cpp
// Accepted
#include <bits/stdc++.h>

using namespace std;

int main()
{
	vector<int> v;
	string aux;
	string s;
	int pos1, pos2;
	int ans = 0;

	while (getline(cin, s))
	{
		if (s == "*") return 0;
		aux.push_back('a');
		aux += s;
		aux.push_back('a');

		int n = aux.size();

		for (int i = 1; i < n; ++i)
		{
			int a = (int)(aux[i] - aux[i - 1] + 26);
			v.push_back(a % 26);
		}
		sort(v.begin(), v.end());

		ans = 0;
		pos1 = 0;
		while (pos1 < v.size() && v[pos1] == 0) ++pos1;

		if (pos1 == v.size()) cout << "0\n";
		else
		{
			pos2 = v.size() - 1;
			while (pos2)
			{
				++ans;
				v[pos2] = (v[pos2] + 1) % 26;
				v[pos1] = (v[pos1] - 1) % 26;
				while (pos1 < v.size() && (v[pos1] == 0 || v[pos1] == v[pos2])) ++pos1;
				if (pos1 == v.size()) break;
				while (pos2 && !(v[pos2])) --pos2;
			}
			if (v[pos2]) ans += 26 - v[pos2];
			cout << ans << '\n';
		}
		v.clear();
		aux.clear();
	}

}
