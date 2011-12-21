#include<iostream>
#include<algorithm>
using namespace std;
int arr[100000];
int k,N;
int main(){
	cin >> N;
	for(int i=0;i<N;i++)
		cin >> arr[i];
	int start,end;int p=1;
	while(p){
		p=0;
		start=0;end=1;
		while(end<=N){
			if(arr[end-1]>arr[end] && end!=N)
				end++;
			else{
				if(start!=end-1){
					k++,reverse(arr+start,arr+end);
					p=1;
				}
				start=end;
				end++;
			}
		}
	}
	cout << k << endl;
	return 0;
}
