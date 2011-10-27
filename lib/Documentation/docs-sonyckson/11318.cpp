//  PROBLEMITA DE LAS CANICAS....: UNO CLKW y el otro ANTICLOCK.... :)
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
#define ll long long
ll arr[50001];
int n;
ll distd(int k, int ind){
	if( ind > k ) return ind-k;
	return n-k+ind;
}
ll disti(int k, int ind){
	if( k > ind ) return k-ind;
	return n-ind+k;
}
int M = 40000000;
int main(){
	int i,j ,k, ind, vaux;;
	int casos;scanf("%i", &casos);
	ll sumi, sumd, a1[50001], a2[50001];
	for(int h=0;h<casos;h++){
		scanf("%i", &n);
		for(i=0;i<n;i++) scanf("%lld", &arr[i]);
		sumi=0, sumd=0, ind = 0, vaux = 0;
		a1[0] = 0;
		for(i=1;i<n;i++) a1[i] = arr[i]*i+a1[i-1];
		a2[n-1] = arr[n-1];
		for(i=n-2;i>=0;i--) a2[i] = arr[i]*(n-i)+a2[i+1];
		a2[0] = 0;
		ll canicasd=0, canicasi=0;
		ind=0;
		while(a1[(ind+1)%n] < a2[(ind+2)%n])ind=(ind+1)%n;
		ind = (ind+1)%n;
		if( a1[ind] != a2[(ind+1)%n]){
			ll a = a1[ind-1];
			ll b = a2[(ind+1)%n];
			ll p = (b+(arr[ind]*disti(0,ind))-a)/n;
			for(i=1;i<ind;i++) canicasd+=arr[i];
			canicasd+=p;
			sumd = a1[ind-1]+p*ind;
			for(i=n-1;i>ind;i--)canicasi+=arr[i];
			canicasi+=(arr[ind]-p);
			sumi = a2[(ind+1)%n]+(arr[ind]-p)*disti(0,ind);
			vaux = p;
		}else{
			vaux = arr[ind];
			for(i=1;i<=ind;i++) canicasd+=arr[i];
			sumd = a1[ind];
			for(i=n-1;i>ind;i--)canicasi+=arr[i];
			sumi = a2[(ind+1)%n];
		}
		ll res = 0, nsol=0;
		if( sumi == sumd ) res+=sumi, nsol++;
		for(k=1;k<n;k++){
			if( k != ind ){
				canicasi+=arr[k-1];
				sumi+=canicasi;
				sumd-=canicasd;
				canicasd-=arr[k];
			}else{
				canicasi+=arr[k-1];
				sumi+=canicasi;
				sumd-=canicasd;
				canicasd-=vaux;
				canicasi-=(arr[k]-vaux);
				sumi-=(arr[k]-vaux)*n;
				ind=(ind+1)%n;
				vaux = 0;
			}
			canicasd+=(arr[ind]-vaux);
			sumd+=(arr[ind]-vaux)*distd(k,ind);
			canicasi-=(arr[ind]-vaux);
			sumi-=(arr[ind]-vaux)*disti(k,ind);
			vaux = arr[ind];
			while(    sumd     <      sumi     ){
				ind=(ind+1)%n;
				sumd+=arr[ind]*distd(k,ind);
				canicasd+=arr[ind];
				sumi-=arr[ind]*disti(k,ind);
				canicasi-=arr[ind];
				vaux = arr[ind];
			}
			if( sumd != sumi ){
				sumd-=arr[ind]*distd(k,ind);
				canicasd-=arr[ind];
				ll a = sumd;
				ll b = sumi;
				ll p = (b+(arr[ind]*disti(k, ind))-a)/n;
				canicasd+=p;
				sumd+=p*distd(k,ind);
				canicasi+=arr[ind]-p;
				sumi+=(arr[ind]-p)*disti(k,ind);
				vaux = p;
			}
			if( sumi == sumd){
				res+= sumi, nsol ++;
			}
		}
		printf("%lld %lld\n", nsol, res);
	}return 0;
}
