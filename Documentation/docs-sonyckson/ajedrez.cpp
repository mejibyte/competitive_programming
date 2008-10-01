// PORFAVOR NUNCA BORRAR ESTE PROBLEMA::: COSTO UN OJO DE LA CARA....

#include <algorithm>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <stack>
#include <sstream>
#include <queue>

#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>

#define forn(i, n) for(int i=0;i<int(n);i++)
#define foreach(it, c)  for(typeof((c).begin()) it = (c).begin();it!=(c).end();++it)
#define ALL(x)   (x).begin(),(x).end()
#define SORT(x) sort(ALL(x))
using namespace std;
#define VI vector<int>
#define VS vector<string>
int table[15];
int N,cant;
short pre[365597][14];
int res = 0;
#include <time.h>
char arr[16][16];
int ar[14];
int tr(int ind){
	forn(i, 14){
		int k = pre[ind][i];
		if(arr[i][k]=='*')return 0;
	}
	return 1;
}
void bick(int paso, int columna, int subida, int bajadas){
	if(paso==14) {
		forn(i, 14) pre[cant][i] = ar[i];
		cant++;
		return;
	}
	for(int i = 0, b = 1; i < N; i++, b <<= 1){
		if(!(columna&b) && !(subida&(1<<(paso+i))) && !(bajadas&(1<<(paso-i+N-1)))&&!(table[paso]&b)){
			ar[paso] = i;
			bick(paso+1, columna^b, subida^(1<<(paso+i)),bajadas^(1<<(paso-i+N-1)));
		}
	}
}
int M[1<<15];
void back(int paso, int columna, int subida, int bajadas){
	if(paso==N-1) {
		printf("hola\n");
		for(int i = 0, b = 1; i < N; i++, b <<= 1){
			if(!(columna&b) && !(subida&(1<<(paso+i))) && !(bajadas&(1<<(paso-i+N-1)))&&!(table[paso]&b))
				res++;
		}
		return;
	}
	if(paso==0){	
		for(int i = 0, b = 1; i < N; i++, b <<= 1)
			if(!(table[paso]&b))
				back(paso+1, columna^b, subida^(1<<(paso+i)),bajadas^(1<<(paso-i+N-1)));
		return;
	}
	int tmp = columna & (subida/(1<<paso)) & (bajadas/(1<<//& table[paso];
	int b;
	while(b=(-tmp&tmp)){
		back(paso+1, columna^b, subida^(1<<(paso+M[b])),bajadas^(1<<(paso-M[b]+N-1)));
		printf("hoa\n");
	}
}
int main(){
	for(int i=0;i<15;i++) M[1<<i] = i;
	cant=0;
	N=14;
	int i,j ,k, b;
	int casos = 0;
	int ans[]={0,0, 0, 0, 2, 10, 4, 40, 92, 352, 724, 2680, 14200, 73712, 365596, 2279184 };
// 	bick(0,0,0,0);
	//printf("%i cant\n", cant);
	while(1){
		scanf("%i", &N);
		if(N==0)return 0;
		casos++;
		for(i=0;i<N;i++)table[i]=0;
		k=0;
		for(i=0;i<N;i++){
			scanf("%s", arr[i]);
			for(j=0, b = 1;j<N;j++, b<<=1){
				if(arr[i][j]=='*'){table[i]^=b;k++;}
			}
		}
		/*
		if(N==14){
			res=0;
			forn(i, 365596){
				if(tr(i))res++;
			}
		}
		else{*/
		res = 0;
		//if(k>0)
		back(0,0,0,0);
		//	else res = ans[N];
		//}
		printf("Case %i: %i\n",casos, res);
	}
	return 0;
}
