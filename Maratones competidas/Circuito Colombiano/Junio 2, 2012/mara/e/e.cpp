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

# define foreach (x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
# define D(x) cout << #x " = " << (x) << endl
# define For(i, a,  b) for (int i = (a); i < (b); i++)

struct State {
	int b[3];
	
	int hash() const {
		return b[0] + 65*b[1] + 65*65*b[2];
	}
	
	bool operator < (const State &t) const {
		return hash() < t.hash();
	}
};

map<State, int> d;
map<State, State> from;

char buffer[1024];

void print(State t) {
	set<State> seen;
	
	vector<string> ans;
	
	
	while (true) {
		sprintf(buffer, "%4d%4d%4d\n", t.b[0], t.b[1], t.b[2]);
		ans.push_back(string(buffer));
		
		assert(seen.count(t) == 0);
		seen.insert(t);

		if (from.count(t) == 0) break;
		t = from[t];
	}
	for (int i = ans.size() - 1; i >= 0; --i) {
		printf("%s", ans[i].c_str());
	}
}

void solve(int a, int b, int c) {
	State start;
	start.b[0] = a;
	start.b[1] = b;
	start.b[2] = c;
	d.clear();
	from.clear();
	
	
	queue<State> q;
	q.push(start);
	d[start] = 0;

	bool solved = false;
	while (q.size() > 0) {
		State cur = q.front(); q.pop();
		
		if (cur.b[0] == cur.b[1] and cur.b[1] == cur.b[2]) {
			// poner la respuesta aqui
			print(cur);
			solved = true;
			break;
		}
		
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				if (i == j) continue;
				// mover de i a j
				if (cur.b[i] < cur.b[j]) continue;
				
					int take = cur.b[j];
					State next = cur;
					next.b[i] -= take;
					next.b[j] += take;
					
					if (d.count(next)) continue;
					d[next] = d[cur] + 1;
					from[next] = cur;
					q.push(next);
			}
		}
		
	}
	
	if (!solved) print(start);
	For(i, 0, 12) printf("="); puts("");
}


int main(){
	int a, b, c;
	while (cin >> a >> b >> c) {
		solve(a, b, c);
		if (a == 0 and b == 0 and c == 0) break;
	}
	return 0;
}


