#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int uint;
typedef unsigned long long int uint64;

#define forsn(i, s, n)		for (uint i = (s); i < (n); i++)
#define forn(i, n)		forsn (i, 0, n)

#define num_diagonals(n)	(2 * (n) - 1)

typedef vector<uint64> vuint64;
typedef vector<vuint64> vvuint64;

#define BLACK 0
#define WHITE 1
// m: output matrix, should have 2 rows and k + 1 columns
// black_white == 1 iff we are dealing with the white cells and an odd value of n 
vuint64 *put_bishops_monochrome(uint n, uint k, bool black_white, vvuint64& m) {
	bool row = 0;

	m[0][0] = 1; // we can always put 0 bishops
	m[1][0] = 1;
	
	forn (i, n - black_white) {
		uint num_cells = 2 * (i / 2) + 1 + black_white;
		forsn (j, 1, k + 1) {
			m[row][j] = m[!row][j] + m[!row][j - 1] * (num_cells - (j - 1));
		}
		row = !row;
	}
	return &m[!row];
}

uint64 put_bishops(uint n, uint k) {
	if (k == 0) return 1;
	if (k == 1 && n == 1) return 1;
	if (k > num_diagonals(n) - 1) return 0;

	vvuint64 matrix_black(2, vuint64(k + 1, 0));
	vvuint64 matrix_white(2, vuint64(k + 1, 0));

	vuint64& black(*put_bishops_monochrome(n, k, BLACK, matrix_black));
	vuint64& white(n % 2 == 0 ? black : *put_bishops_monochrome(n, k, WHITE, matrix_white));

	uint64 ways = 0;
	uint lower = k > (n - 1) ? k - (n - 1) : 0;
	uint upper = min(k, n - 1) + 1;
	forsn (a, lower, upper) {
		ways += black[a] * white[k - a];
	}
	return ways;
}

int main() {
	uint n, k;
	while (true) {
		scanf("%u %u", &n, &k);
		if (n == 0 && k == 0) break;
		cout << put_bishops(n, k) << endl;
	}
	return 0;
}

