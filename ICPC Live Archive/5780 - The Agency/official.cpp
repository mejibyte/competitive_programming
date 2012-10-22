#include <iostream>
using namespace std;

const int MAXN = 1000;

bool src[MAXN], dst[MAXN];
int costs[MAXN];
bool extra[MAXN];		// true if should make extra move on 1->1 node

typedef long long LL;

int main()
{
	int ncase, n;
	LL s;		// sum of bits going from 1 to 0
	LL r;		// sum of bits staying at 1;
	LL t;		// sum of any src bit = 1;
	LL nchange;	// number of bits where src != dst
	cin >> ncase;
	for(int icase=1; icase<=ncase; icase++) {
		cin >> n;
		for(int i=0; i<n; i++) {
			char ch;
			cin >> ch;
			src[i] = (ch == '1');
		}
		for(int i=0; i<n; i++) {
			char ch;
			cin >> ch;
			dst[i] = (ch == '1');
		}
		LL m=0;
		s = 0, r = 0, t = 0, nchange = 0;
		for(int i=0; i<n; i++) {
			int val;
			cin >> val;
			if (src[i] || dst[i]) {
				if (src[i]) {
					t += val;
					if (!dst[i])
						s += val;
					else
						r += val;
				}
				else if (dst[i])
					s += val;
				if (src[i] != dst[i])
					nchange++;
				LL j=m;
				LL savsrc = src[i];
				LL savdst = dst[i];
				while (j>0 && costs[j-1] < val) {
					costs[j] = costs[j-1];
					src[j] = src[j-1];
					dst[j] = dst[j-1];
					j--;
				}
				costs[j] = val;
				src[j] = savsrc;
				dst[j] = savdst;
				m++;
			}
			extra[i] = false;
		}
										// process
		LL start = 0;
		LL change = 0;
		for(int i=0; i<m; i++) {
			if (src[i]) {
				if (!dst[i]) {
					s -= costs[i];
					nchange--;
				}
				else {
					change += 2*r-costs[i] + s;		// deficit of extra move
					change -= nchange*costs[i];		// benefit of extra move
					if (change < 0) {	// better to take extra moves
						for(int j=start; j<=i; j++) {
							if (src[j] && dst[j]) {
								extra[j] = true;
							}
						}
						change = 0;
						start = i+1;
					}
					r -= costs[i];
				}
			}
			else {
				s -= costs[i];
				nchange--;
			}
		}

		LL totcost = 0;
		for(int i=0; i<m; i++) {
			if (src[i]) {
				if (!dst[i] || extra[i]) {
					t -= costs[i];
					totcost += t;
				}
			}
		}

		for(int i=m-1; i>=0; i--) {
			if (!src[i] || extra[i]) {
				t += costs[i];
				totcost += t;
			}
		}
		cout << "Case " << icase << ": " << totcost << endl;
	}
}
