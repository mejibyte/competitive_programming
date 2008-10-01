#include <string>
#include <iostream>
#include <cstdio>
using namespace std;

int FT[1<<20];
int MX =  1 << 20;

void update(int ind, int val){
	while ( ind <= MX ){
		FT[ind]+= val;
		ind += (ind&-ind);
	}
}
int query(int ind ){
	int res = 0;
	while( ind ){
		res += FT[ind];
		ind -= (ind&-ind);
	}
	return res;
}
int get(int val, int b, int e){
	while( b + 1 < e ){
		int med = ( b + e ) / 2 ;
		if( query(med) >= val ) e = med;
		else b = med;
	}
	return e;
}
int main(){
	int i,j,k;int casos; cin >> casos;
	for(int h = 0 ; h < casos; h ++ ){
		int N; cin >> N;
		int arr[1000010];
		memset(FT, 0, sizeof(FT));
// 		printf("ACA TAAAA\n");
		for(i=1;i<=N;i++){
			update(i, 1);
		}
// 		printf("ACA TAAAA\n");
		
		int cant = N;
		int place = N;
		for(i=0;i<N;i++){
// 			for(j=1;j<=N;j++) printf("%i ", query(j));printf("\n");
			place = ( place + i ) % cant;
			cant--;
			int ind = get(place+1,0, N+1);
			update(ind,-1);
			arr[ind] = i+1;
		}
		cout << "Case #" << h+1 << ":";
		int Q; cin >> Q;
		for(i=0;i<Q;i++){
			cin >> k;
			cout << " " << arr[k];
		}
		cout << endl;
	}return 0;
}
