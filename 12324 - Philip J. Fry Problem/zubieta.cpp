#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <deque>
#include <sstream>
#include <list>
#include <set>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int n;
int viajes[105];
int bolas[105];
int mat[105][105*105];

int func(int a, int b, bool c){
	if(mat[a][b])
		return mat[a][b];

	int thisTravel = viajes[a]/(c?2:1);
	b += bolas[a];
	if(a!=n-1)
		if(b)
			mat[a][b] = (thisTravel += min(func(a+1,b-1,1),func(a+1,b,0)));
		else
			mat[a][b] = (thisTravel += func(a+1,b,0));
	
	return thisTravel;
}

int main(){
	scanf("%d",&n);
	while(true){
		if(!n){
			break;
		}
		for(int z=0;z<n;++z){
			scanf("%d",&viajes[z]);
			scanf("%d",&bolas[z]);
		}
		for(int z=0;z<n;++z)
			for(int y=0;y<n*n;++y)
				mat[z][y]=0;
		printf("%d\n",func(0,0,0));
		scanf("%d",&n);
	}
}