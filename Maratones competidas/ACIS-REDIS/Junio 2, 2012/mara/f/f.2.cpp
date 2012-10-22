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

const long double eps = 1e-9;
int cmp(double x, double y, double tol = eps) {
	return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

const int MAXN = 200;

bool know[MAXN][MAXN];
long double c[MAXN][MAXN];
int n1, n2;
vector<string> u1, u2;
int nextId;
map<string, int> id;

int getId(const string &s) {
	if (id.count(s)) return id[s];
	return id[s] = nextId++;
}

void trim(string &s) {
	while (s.size() > 0 and s[0] == ' ') s = s.substr(1);
	while (s.size() > 0 and s[s.size() - 1] == ' ') s.resize(s.size() - 1);
}


void despejar() {
	int n = n1 + n2;
	
	for (int i = 0; i < n; ++i) {
		know[i][i] = true;
		c[i][i] = 1.0;
	}
	
	bool change = true;
	while (change) {
		change = false;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (know[i][j]) continue;
				for (int k = 0; k < n; ++k) {
					if (know[i][k] and know[k][j]) {
						know[i][j] = true;
						c[i][j] = c[i][k] * c[k][j];
						change = true;
					}
				}
			}
		}
	}
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			assert(know[i][j]);
			//assert(c[i][j] != 0);
		}
	}
}

void convertir(const string &s) {
	int base = getId(u2.back());
	
	long double remain = 0;
	stringstream sin(s);
	long double a; string u;
	while (sin >> a >> u) {
		remain += a * c[getId(u)][base];
	}

	for (int i = 0; i < n2 - 1; ++i) {
		int index = getId(u2[i]);
		assert(know[index][base]);
		//assert(c[index][base] != 0);
		
		int t = 0;
		while (cmp(remain, c[index][base]) >= 0) {
			t++;
			remain -= c[index][base];
		}
		printf("%d %s ", t, u2[i].c_str());		
	}
		
	// imprimir el ultimo redondeado
	printf("%.0lf %s\n", (double)remain, u2.back().c_str());
}

void read_rule() {
	long double a, b;
	string p, q, s;
	
	cin >> a >> p >> s >> b >> q;
	//assert(s == "=");
	
	int pp = getId(p), qq = getId(q);
	know[pp][qq] = true;
	c[pp][qq] = b / a;
	
	know[qq][pp] = true;
	c[qq][pp] = a / b;	
}

int main(){	
	while (true) {
		u1.clear();
		u2.clear();
		id.clear();
		nextId = 0;
		memset(know, 0, sizeof know);
		memset(c, 0, sizeof c);
		
		string s;
		if (!getline(cin, s)) break;
		trim(s);
		if (s == "") break;
		
		stringstream sin(s);
		for (; sin >> s; ) {
			u1.push_back(s);
		}
		n1 = u1.size();
		
		for (int i = 0; i < n1 - 1; ++i) {
			read_rule();
		}
		getline(cin, s);

		getline(cin, s);
		sin.clear();
		sin.str(s);
		
		for (; sin >> s; ) {
			u2.push_back(s);
		}
		n2 = u2.size();
		
		for (int i = 0; i < n2 - 1; ++i) {
			read_rule();	
		}
		
		// conversion
		{
			read_rule();		
		}
		
		despejar();
		getline(cin, s);
		
		while (getline(cin, s)) {
			trim(s);
			if (s == "") break; // se acabo el caso
			convertir(s);
		}
	}

	return 0;
}


