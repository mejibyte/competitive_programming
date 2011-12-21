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
#pragma comment(linker,"/STACK:64000000")
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
void error(){int ttt=0; cout << 7/ttt;}
LL gcd(LL a, LL b) {
	return (!a)?b:gcd(b%a,a);
}
int mod=1000*1000*1000+7;
inline int MUL(int a, int b) {return 1ll*a*b%mod;}
inline int ADD(int a, int b) {return (a+b>=mod)?a+b-mod:a+b;}
inline int SUB(int a, int b) {return (a-b<0)?a+mod-b:a-b;}


int A[111111];
int B[111111];

LL go(int a, int b) {
	if (b-a+1<=1) return 0;
	int m=(a+b)/2;
	LL r=go(a,m)+go(m+1,b);
	int p1=a;
	int p2=m+1;
	int c=m-a+1;

	int pp=a;
	while(p1<=m || p2<=b) {
		if (p1>m) {
			B[pp++]=A[p2++];
			r+=c;
		} else if (p2>b) {
			B[pp++]=A[p1++];
			--c;
		} else {
			if (A[p1]<A[p2]) {
				B[pp++]=A[p1++];
				--c;
			} else {
				B[pp++]=A[p2++];
				r+=c;
			}
		}
	}
	FOR(i,a,b+1) A[i]=B[i];
	return r;
}

int main() {	
#ifdef NEV_DEBUG
    freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	 
    clock_t beg = clock();
#else
    //freopen("bricks.in","r",stdin);
    //freopen("bricks.out","w",stdout);	 
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	int n=gi();
	FOR(i,0,n) {
		A[i]=gi();
	}
	A[n]=1<<30;
	LL res=0;
	int b0=0;
	FOR(i,0,n) {
		if (A[i+1]>A[i]) {
			if (b0!=i) {
				reverse(A+b0,A+i+1);
				++res;
			}
			b0=i+1;
		}
	}
	res+=go(0,n-1);
	cout << res << endl;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef NEV_DEBUG
	fprintf(stderr,"*** Total time: %.3lf ***\n",1.0*(clock()-beg)/CLOCKS_PER_SEC);
#endif
    return 0;
}