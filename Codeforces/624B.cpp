#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	ll t;	cin>>t;
	while(t--){
		ll n,m;	cin>>n>>m;
		int arr[n];
		int pos[m];
		for(int i=0;i<n;i++){
			cin>>arr[i];
		}
		ll temp;
		for(int i=0;i<m;i++){
			cin>>temp;
			pos[i]=temp-1;
		}
		sort(pos,pos+m);
		char s[n-1];
		for(int i=0;i<n-1;i++){
			s[i]='0';
		}
		for(int i=0;i<m;i++){
			s[pos[i]]='1';
		}
		int max_elem=-1;
		bool flag=true;
		for(int i=0;i<n-1;i++){
			max_elem=max(max_elem,arr[i]);
			if(s[i]=='0' && max_elem>arr[i+1]){
				flag=false;
				break;
			}
		}
		if(flag)
			cout<<"YES\n";
		else
			cout<<"NO\n";

	}	
	return 0;
}