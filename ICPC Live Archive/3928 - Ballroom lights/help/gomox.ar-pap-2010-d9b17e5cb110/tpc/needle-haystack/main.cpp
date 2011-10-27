#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;

typedef unsigned long long int lluint;
typedef vector<int> vint;

#define forsn(i, s, n)	for (int i = (s); i < (n); i++)
#define forn(i, n)	forsn (i, 0, n)

// Pre KMP

void pkmp(const string& s, vint& f) {
	int z = f[0] = -1;
	forsn (i, 1, s.size() + 1) {
		while (z != -1 && s[i - 1] != s[z]) z = f[z];
		f[i] = ++z; // z might be -1
	}
}

// Buffer

#define TAMBUF	65536
lluint pos;
char buf[TAMBUF];
int buf_size;

#define buf_sync() { \
	cin.getline(buf, TAMBUF + 1); \
	pos += buf_size; \
	buf_size = cin.gcount(); \
	cin.clear(); \
}

#define buf_start() { \
	buf_sync(); \
	pos = 0; \
}

// KMP

void kmp(const string& s, vint& f) {
	buf_start();
	const int final = s.size();
	int state = 0;
	while (true) {
		forn (i, buf_size) {
			if (state == final) {
				cout << (pos + i - final) << " ";
			}
			while (s[state] != buf[i]) {
				state = f[state];
				if (state == -1) break;
			}
			state++;
		}
		if (buf_size < TAMBUF) break;
		buf_sync();
	}
}

int main() {
	for (;;) {
		int needle_size;
		string needle;
		cin >> needle_size;
		if (cin.eof()) break;
		cin >> needle;
		assert(needle_size == needle.size());
		cin.ignore(1);

		vint f(needle.size() + 1);
		pkmp(needle, f);
		kmp(needle, f);
		cout << endl;
	}
	return 0;
}

