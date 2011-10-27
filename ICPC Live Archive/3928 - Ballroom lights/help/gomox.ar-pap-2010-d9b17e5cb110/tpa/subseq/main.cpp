#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <cstdio>

using namespace std;

typedef unsigned int uint32;

#define forsn(i, s, n)	for (uint32 i = (s); i < (n); i++)
#define forn(i, n)	forsn (i, 0, n)
#define dforn(i, n)	for (uint32 i = (n); i-- > 0;)

// BigInt
// Represents a number in 0 <= n < 10 ** 128

#define BigInt_NDIGITS	16
#define BigInt_BASE	100000000
class BigInt {
public:
	BigInt() : _digits(BigInt_NDIGITS, 0) {}

	BigInt(uint32 n) : _digits(BigInt_NDIGITS, 0) {
		assert(n < BigInt_BASE);
		_digits[0] = n;
	}

	// For testing
	BigInt(const string& s) : _digits(BigInt_NDIGITS, 0) {
		uint32 pow = 1;
		uint32 digit = 0;
		uint32 j = 0;
		dforn (i, s.size()) {
			assert('0' <= s[i] && s[i] <= '9');
			digit += pow * (s[i] - '0');

			pow *= 10;
			if (pow == BigInt_BASE) {
				_digits[j++] = digit;
				digit = 0;
				pow = 1;
			}
		}
		assert(j < BigInt_NDIGITS || digit == 0);
		if (j < BigInt_NDIGITS) {
			_digits[j] = digit;
		}
	}

	BigInt operator+(const BigInt& n) {
		BigInt res;
		bool carry = 0;

		forn (i, BigInt_NDIGITS) {
			const uint32 r = _digits[i] + n._digits[i] + carry;
			if (r >= BigInt_BASE) {
				res._digits[i] = r % BigInt_BASE;
				carry = 1;
			} else {
				res._digits[i] = r;
				carry = 0;
			}
		}
		assert(carry == 0);
		return res;
	}

	void print() {
		bool zero = true; 
		dforn (i, BigInt_NDIGITS) {
			if (zero) {
				if (_digits[i] == 0) continue;
				printf("%u", _digits[i]);
				zero = false;
			} else {
				printf("%.8u", _digits[i]);
			}
		}
		if (zero) {
			printf("0");
		}
	}

private:
	// Least significant digit first.
	// Digits are in 0 <= d < BigInt_BASE
	vector<uint32> _digits;
};

#define print_bigint(x)	(x).print()

typedef vector<BigInt> vBigInt;
typedef vector<vBigInt> vvBigInt;
BigInt distinct_subsequences(const string& x, const string& z) {
	vvBigInt m(2, vBigInt(z.size() + 1, BigInt(0)));

	m[0][0] = BigInt(1);
	m[1][0] = BigInt(1);
	bool row = 1;
	forsn (i, 1, x.size() + 1) {
		forsn (j, 1, z.size() + 1) {
			if (x[i - 1] == z[j - 1]) {
				m[row][j] = m[!row][j] + m[!row][j - 1];
			} else {
				m[row][j] = m[!row][j];
			}
		}
		row = !row;
	}
	return m[!row][z.size()];
}

int main(int argc, char **argv) {
	uint32 n;
	cin >> n;
	char c;
	cin.get(c);
	forn (i, n) {
		string x, z;
		getline(cin, x);
		getline(cin, z);
		print_bigint(distinct_subsequences(x, z));
		cout << endl;
	}
	return 0;
}

