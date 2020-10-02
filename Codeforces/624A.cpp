#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	ll t;	cin>>t;
	while(t--){
		ll a,b;
		cin>>a>>b;
		ll ans=0;
		ll diff=b-a;
		if(diff==0){
			ans=0;
		}
		else if(diff<0){
			diff*=-1;
			if(diff & 1){
				ans=2;
			}
			else{
				ans=1;
			}
		}
		else{
			if(diff & 1){
				ans=1;
			}
			else{
				ans=2;
			}
		}
		cout<<ans<<"\n";
	}	
	return 0;
}