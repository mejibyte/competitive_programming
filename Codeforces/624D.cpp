#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void swap(int *xp, int *yp)  
{  
    int temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
}  
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
		bool flag=true;
		sort(pos,pos+m);
		int i, j;  
    	for (i = 0; i < n-1; i++){ 
    		for (j = 0; j < n-i-1; j++)  
        		if (arr[j] > arr[j+1]) {
        			if(! binary_search(pos,pos+m,j)){
        				flag=false;
        				break;
        			}
					else
            			swap(&arr[j], &arr[j+1]);
        		} 
        		if(!flag)
        			break;
        }
		
		if(flag)
			cout<<"YES\n";
		else
			cout<<"NO\n";

	}	
	return 0;
}