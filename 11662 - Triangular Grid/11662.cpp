#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <cassert>
#include <cstdio>

using namespace std;

int B, H;

int myFloor(int a, int b) {
	if ((a < 0) ^ (b < 0)) { // negative
		return -(abs(a)/abs(b)) - 1;
	} else {
		return abs(a)/abs(b);
	}
}

int mod(int a, int b) {
	return (a % b + b) % b;
}

int Kh(int x, int y) {
	return myFloor(y, H);
}

int Ka(int x, int y) {
	return myFloor(2*H*x - B*y, 2*H*B);
}

int Kv(int x, int y) {
	return myFloor(2*H*x + B*y, 2*H*B);
}

bool isVertex(int x, int y) {
    assert(B % 2 == 0);
	if (mod(y, H) != 0) return false;
	int q = y / H;
	if (q % 2 == 0) return mod(x, B) == 0;
	return mod(x, B) == (B/2);
}


int main() {    
	int x1, y1, x2, y2;
	while (cin >> B >> H >> x1 >> y1 >> x2 >> y2) {
		if (B == 0 and H == 0 and x1 == 0 and y1 == 0 and x2 == 0 and y2 == 0) break;
		B *= 2;
        x1 *= 2;
        x2 *= 2;
  		
		int ans = abs(Kh(x1, y1) - Kh(x2, y2)) + abs(Ka(x1, y1) - Ka(x2, y2)) + abs(Kv(x1, y1) - Kv(x2, y2));
		ans++;
		
		int dx = x2 - x1;
		int dy = y2 - y1;
		int g = __gcd(abs(dx), abs(dy));
		dx /= g; dy /= g;

		assert(!isVertex(x1, y1));
		assert(!isVertex(x2, y2));

		int x = x1, y = y1;
		while (x != x2 or y != y2) {
			ans -= 2 * isVertex(x, y);
			x += dx;
			y += dy;
		}
		
		cout << ans << endl;
	}
	return 0;
}
