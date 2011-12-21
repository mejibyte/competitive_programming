#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <complex>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <complex>
#include <stack>
#include <cassert>
#include <memory.h>
#ifdef NEV_DEBUG
#include <ctime>
#endif
using namespace std;
const double pi = 3.1415926535897932384626433832795;
double eps=1e-9; 
//double eps=1e-15; // atan up to 1e-15

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int,int> PII;

#define sz size()
#define mp make_pair
#define pb push_back
#define FOR(i,a,b) for(int i=(a),_b(b); i<_b; ++i)
#define RFOR(i,a,b) for(int i=(a)-1,_b(b); i>=_b; --i)
#define CLR(a,b) memset(a,b,sizeof(a))
#define CPY(a,b) memcpy(a,b,sizeof(a))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define sqr(a) ((a)*(a))

char ch[1<<20];
inline string gs() {scanf("%s",ch); return string(ch);}
inline string gl() {gets(ch); return string(ch);}
inline int gi() {int x;scanf("%d",&x); return x;}

int N;
int A[32][32];
int B[500100][30];
void pre(int start, int mx) {
	CLR(B,0);
	vector<int> a;
	vector<VI> b;
	FOR(i,0,N) FOR(j,0,N) a.pb(A[i][j]);
	sort(a.begin(),a.end());
	a.erase(unique(a.begin(),a.end()),a.end());
	FOR(i,0,a.sz) b.pb(VI(N,0));
	FOR(i,0,N) FOR(j,0,N) FOR(k,0,a.sz) if (A[i][j]==a[k]) {
		b[k][i]|=(1<<j);
	}
	FOR(i,0,a.sz) {
		int h=0;
		while(h<start+500100 && h<mx) {
			if (h>=start) {
				FOR(j,0,N) B[h-start][j]|=b[i][j];
			}
			h+=a[i];
		}
	}
}

int main() {	
#ifdef NEV_DEBUG
    //freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	 
    clock_t beg = clock();
#else
    //freopen("bricks.in","r",stdin);
    //freopen("bricks.out","w",stdout);	 
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	N=gi();
	int T=gi();
	int x1=gi();
	int y1=gi();

	FOR(i,0,N) FOR(j,0,N) {
		A[i][j]=gi();
	}

	int mm=(1<<N)-1;
	int X[2][30]={0};
	X[0][x1-1]|=(1<<(y1-1));
	int last=0;
	int cur=1;
	pre(0,T+10);
	FOR(t,1,T+1) {
		if (t==500100) pre(500100,T+10);
		int tt=t;
		if (tt>500100) tt-=500100;
		CLR(X[cur],0);
		FOR(i,0,N) {
			if (i-2>=0) X[cur][i-2]|=(X[last][i]<<1)|(X[last][i]>>1);
			if (i-1>=0) X[cur][i-1]|=(X[last][i]<<2)|(X[last][i]>>2);
			if (i+1< N) X[cur][i+1]|=(X[last][i]<<2)|(X[last][i]>>2);
			if (i+2< N) X[cur][i+2]|=(X[last][i]<<1)|(X[last][i]>>1);
		}
		FOR(i,0,N) {
			X[cur][i]&=mm;
			X[cur][i]&=B[tt][i];
		}
		cur^=1;
		last^=1;
	}

	vector<PII> A;
	FOR(i,0,N) {
		FOR(j,0,N) if (X[last][i]&(1<<j)) A.pb(mp(1+i,1+j));
	}
	printf("%d\n",A.sz);
	FOR(i,0,A.sz) {
		printf("%d %d\n",A[i].first,A[i].second);
	}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef NEV_DEBUG
	fprintf(stderr,"*** Total time: %.3lf ***\n",1.0*(clock()-beg)/CLOCKS_PER_SEC);
#endif
    return 0;
}