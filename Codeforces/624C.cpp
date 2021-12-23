#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	ll t;	cin>>t;
	while(t--){
		ll n,m;
		cin>>n>>m;
		string s;
		cin>>s;
		ll temp;
		ll arr[n]={0};
		for(int i=0;i<m;i++){
			cin>>temp;
			arr[0]++;
			if(temp!=n)
				arr[temp]--;
		}
		for(int i=1;i<n;i++){
			arr[i]+=arr[i-1];
		}
		map<char,int> ans;
		for(int i=0;i<n;i++){
			ans[s[i]]+=arr[i];
		}
		for(int i=0;i<n;i++){
			ans[s[i]]++;
		}
		for(char i='a';i<='z';i++){
			cout<<ans[i]<<" ";
		}
		cout<<"\n";
	}	
	return 0;
}