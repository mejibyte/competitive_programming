/* mergesort :) con el contador :) en divide & conquer */
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
#include <cassert>
#define forn(i, n) for(int i=0;i<int(n);i++)
#define foreach(it, c)  for(typeof((c).begin()) it = (c).begin();it!=(c).end();++it)
#define ALL(x)   (x).begin(),(x).end()
#define SORT(x) sort(ALL(x))
using namespace std;
#define VI vector<int>
#define VS vector<string>
#define PB push_back
#define ll long long

int aux[10011];
int caux[10011];


int array[10011], cant[10011], c2[10011], a2[10011], a1[10011], c1[10011];
void back(int b, int e){
	int i,j ,k;
	int n1,n2;
	if( e == b ){
		cant[b] = 0;
		return;
	}else if( e == b+1){
		cant[b] = 0;
		if( array[b] <= array[e] ){
			cant[e] = 0;
			swap(array[b], array[e]);
		}else{
			cant[b] = 0;
			cant[e] = 1;
		}
		return;
	}
	back(b, (b+e)/2);
	back((b+e)/2+1, e);
	for(i=b;i<=(b+e)/2;i++)a1[i-b] = array[i], c1[i-b] = cant[i];
	n1 = (b+e)/2-b+1;
	for(i=(b+e)/2+1;i<=e;i++)a2[i-((b+e)/2+1)] = array[i], c2[i-((b+e)/2+1)] = cant[i];
	n2 = e-((b+e)/2+1)+1;
	a1[n1] = -1; a2[n2] = -1;
	int ind1 = 0, ind2 = 0;
	int cn = n1+n2;
	for(int h = 0 ; h < cn ; h ++ ){
		if( a1[ind1] <= a2[ind2] ){
			aux[h] = a2[ind2];
			caux[h] = c2[ind2] + ind1 ;
			ind2++;
		}else{
			aux[h] = a1[ind1];
			caux[h] = c1[ind1];
			ind1++;
		}
	}
	for(i=b;i<=e;i++){
		array[i] = aux[i-b];
		cant[i] = caux[i-b];
	}
}
int main(){
	int i,j ,k, n;
	scanf("%i %i", &n, &k);
	int best = -1, nodo = -1;
	for(i=0;i<k;i++){
		for(j=0;j<n;j++)scanf("%i", &array[j]);
		back(0, n-1);
		int total = 0;
		for(j=0;j<n;j++)total += cant[j];
		if( total > best ){ best = total, nodo = i;}
	}
	printf("%i\n", nodo+1);
	return 0;
}
