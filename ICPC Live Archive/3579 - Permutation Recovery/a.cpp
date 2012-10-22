// Accepted

#include <iostream>
#include <vector>
#include <cstdio>
#include <cassert>

using namespace std;

int a[505];

int main() {
	int n; while (cin >> n) {
		if (n == 0) break;
		
		vector<int> ans;
		for (int i = 0; i < n; ++i) {
			cin >> a[i];
		}
		
		for (int i = n - 1; i >= 0; --i) {
			int pos = a[i];
			ans.insert(ans.begin() + pos, i + 1);
		}
		assert(ans.size() == n);
		
		for (int i = 0; i < n; ++i) {
			if (i > 0) printf(",");
			printf("%d", ans[i]);
		}
		printf("\n");
	}
    return 0;
}
