/*
 * in the name of god
 *
 *
 *
 *
 *
 *
 *
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <complex>
#include <stack>
#include <deque>
#include <queue>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef complex<double> point;
typedef long double ldb;

const int maxN = 1000 * 1000 + 10;
const int mod  = 1000 * 1000 * 1000 + 7;

int n,m;
int pw[maxN];
int dp[(1<<20)][22];

int bit (int x) { return 1<<x; }

int main(){
	
	scanf("%d%d" , &n, &m);
	for (int i=1; i<=n; i++){
		int len; scanf ("%d" , &len);
		int mask = 0;
		for (int j=1; j<=len; j++){
			int tmp; scanf ("%d" , &tmp);
			mask|=bit(tmp-1);
		}
		dp[mask][m]++;
	}

	pw[0]=1;
	for (int i=1; i<maxN; i++){
		pw[i] = (pw[i-1]<<1);
		if (pw[i]>=mod) pw[i]-=mod;
	}

	for (int i=0; i<(int)bit(m); i++){
		
		int sum=dp[i][m];

		for (int j=m-1; j>=0; j--){
			if (i & bit(m-1-j)){
				dp[i][j] = dp[i-bit(m-1-j)][j];
				sum+=dp[i][j];
			}
			else
				dp[i][j] = sum;
		}
	}

	int ans = pw[n];

	for (int i=1; i<(int)bit(m); i++){
	
		int cur = bit(m)-1-i;
		int tot = dp[cur][m];
		for (int j=m-1; j>=0; j--) if (cur & bit(m-1-j))
			tot+= dp[cur][j];

		if (__builtin_popcount(i)%2)
			ans-=pw[tot];
		else
			ans+=pw[tot];
		
		if (ans<0) ans+=mod;
		if (ans>=mod) ans-=mod;
	}

	cout << ans << endl;

	return 0;
}
