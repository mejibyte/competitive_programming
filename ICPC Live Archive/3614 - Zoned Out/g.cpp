// Accepted

using namespace std;

#include <algorithm>
#include <iostream>
#include <iterator>
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
#include <map>
#include <set>

# define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
# define D(x) cout << #x " = " << (x) << endl
# define For(i, a,  b) for (int i = (a); i < (b); i++)

const int MAXN = 100005;

vector<int> to[MAXN];
int erases[MAXN];
int adds[MAXN];
set<int> seen[MAXN];

void process(int clerk, int mask) {
	mask |= adds[clerk];		
	mask &= ~erases[clerk];	
	adds[clerk] |= mask;
	
	if (seen[clerk].count(mask) == 0) {
		seen[clerk].insert(mask);
		foreach(x, to[clerk]){ 
			process(*x, mask);
		}
	}
}

int main(){
	int B, C;
	while (cin >> B >> C) {
		if (B == 0 and C == 0) break;

		assert(B <= 30);
		assert(C < MAXN);
		
		For(i, 0, C) {
			to[i].clear();
			erases[i] = 0;
			adds[i] = 0;
			seen[i].clear();
		}
		
		string s; getline(cin, s);
		for (int i = 0; i < C; ++i) {
			getline(cin, s);
			stringstream sin(s);
			
			int added = 0;
			for (int bit; sin >> bit; ) added |= (1 << bit);
			adds[i] = added;
			
			int erased = 0;
			getline(cin, s);
			sin.clear();
			sin.str(s);
			for (int bit; sin >> bit; ) erased |= (1 << bit);
			erases[i] = erased;	

			getline(cin, s);
			sin.clear();
			sin.str(s);
			for (int f; sin >> f; ) to[i].push_back(f);		
			
		}
		
		process(0, 0);
		
		int ans = adds[0];
		ans &= ~erases[0];
		
		bool first = true;
		for (int i = 0; i < B; ++i) {
			if (ans & (1 << i)) {
				if (!first) printf(" ");
				first = false;
				printf("%d", i);
			}
		}
		puts("");
	}

	return 0;
}


