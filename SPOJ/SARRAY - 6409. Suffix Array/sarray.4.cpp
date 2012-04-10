using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
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
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

#define f(i, a, b) for (int i = a; i < b; ++i)

const int MAXN = 100005;
int n,t; //n es el tamanho de la cadena
int p[MAXN],r[MAXN],h[MAXN];
char s[MAXN];

bool comp(int i,int j){ return p[i+t] < p[j+t]; }

void suff_arr(){
   int bc[256];
	f(i,0,256) bc[i] = 0;
	f(i,0,n) ++bc[s[i]];
	f(i,1,256) bc[i] += bc[i-1];
	f(i,0,n) r[--bc[s[i]]] = i;
	f(i,0,n) p[i] = bc[s[i]];
	for(t=1; t<n; t *= 2 ){
		for(int i = 0, j = 1; j<n; i = j++ ){
			while( j<n && p[r[j]] == p[r[i]] ) j++;
			if( j-i==1 ) continue;
			int *ini = r+i, *fin = r+j;
			sort(ini, fin, comp);
			int pri = p[*ini+t], num = i, pk;
			for(; ini<fin; p[*ini++] = num ){
				if(((pk=p[*ini+t]) == pri) || (i<=pri && pk<j) ){}
				else pri = pk, num = ini-r;
			}
		}
	}
}

int main(){
    gets(s);
    n = strlen(s) + 1;
    for (int i = 0; i < n; ++i) {
        char c = s[i];
        //assert(0x20 <= c and c <= 0x7E);
    }
    suff_arr();
    for (int i = 1; i < n; ++i) {
        printf("%d\n", r[i]);
    }
    return 0;
}