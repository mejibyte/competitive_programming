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

#include <bitset>

const int MAXN = 85;

struct Person {
	string name;
	bool male;
	bitset<MAXN> bits;
};

map<vector<bool>, vector<string> > pairs;

int main(){
	string types;
	while (cin >> types) {
		pairs.clear();
		int n = types.size();
		
		vector<Person> parents;
		
		string s;
		while (cin >> s and s != "***") {
			Person p;
			p.name = s;
			cin >> s;
			p.male = (s == "M");
			cin >> s;
			p.bits.reset();
			assert(s.size() == n);
			for (int i = 0; i < n; ++i) {
				p.bits[i] = (s[i] == '1');
			}
			parents.push_back(p);
		}

		for (int i = 0; i < parents.size(); ++i) {
			for (int j = i + 1; j < parents.size(); ++j) {
				if (parents[i].male ^ parents[j].male) {
					//printf("%s with %s\n", parents[i].name.c_str(), parents[j].name.c_str());
					
					vector<bool> son(n);
					for (int k = 0; k < n; ++k) {
						if (types[k] == 'D') {
							son[k] = parents[i].bits[k] or parents[j].bits[k];
						} else {
							son[k] = parents[i].bits[k] and parents[j].bits[k];							
						}
					}
					
					//printf("   son: "); For(p, 0, n) printf("%d", (int)son[p]); puts("");
					
					string mom = parents[i].male ? parents[j].name : parents[i].name;
					string dad = parents[i].male ? parents[i].name : parents[j].name;
					pairs[son].push_back(mom + "-" + dad);
				}
			}
		}
		
		string name;
		while (cin >> name and name != "***") {
			cin >> s;
			vector<bool> bits(n);
			for (int i = 0; i < n; ++i) bits[i] = (s[i] == '1');
			
			vector<string> by = pairs[bits];
			sort(by.begin(), by.end());
			
			printf("%s by ", name.c_str());
			for (int i = 0; i < by.size(); ++i) {
				if (i > 0) printf(" or ");
				printf("%s", by[i].c_str());
			}
			puts("");
		}
		
	}
	return 0;
}


