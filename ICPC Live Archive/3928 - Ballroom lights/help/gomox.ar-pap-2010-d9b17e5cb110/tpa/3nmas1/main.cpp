#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

typedef unsigned int uint;
typedef unsigned short ushort;

#define Max_memo	1000001
vector<ushort> d(Max_memo, 0);

#define memorizado(x)	((x) < Max_memo && d[(x)] != 0)
#define next(n)	((n) % 2 == 0 ? (n) / 2 : 3 * (n) + 1)

ushort periodo(uint n) {
	if (memorizado(n)) {
		return d[n];
	} else {
		ushort p = periodo(next(n)) + 1;
		if (n < Max_memo) {
			d[n] = p;
		}
		return p;
	}
}

ushort resolver(uint x, uint y){
	ushort res = 0;
	uint i = min(x,y);
	uint sup = max(x,y);
	ushort aux;
	i = max(sup/2,i);

	while(i <= sup){
		aux = periodo(i);
		if (aux > res){
			res = aux;
		}
		i++;
	}
	return res;
}

int main(int argc, char **argv)
{
	uint x, y;
	d[1] = 1;
	while (scanf("%u %u",&x,&y)==2) {
		cout << x <<" "<< y <<" " << resolver(x, y) << endl;
	}
	return 0;
}

