// MULTI - KNAPSACK   PROBLEM :)

/*
ID: edestef1
LANG: C++
TASK: fence8
*/
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
FILE *fin, *fout;
#define N 1030
int board[51], numb;
int numr;
int rail[N];
vector<int> Rail;
int tot[139];
int SUMA;
int SB;
int desperdicio = 0;
int cortado = 0;
int mx;
int mini;
int go(int quedan, int R, int nb){
	if( quedan == 0 ) return 1; // RIGHT
	if( nb == numb ) return 0;  // RIGHT
	if( R == 0 )return go ( quedan, mx, nb+1);
	if( SUMA - cortado > board[nb] + tot[nb+1]) return 0;
	if( board[nb] < mini )return go ( quedan, mx, nb+1);
	
	if( rail[R] == 0 || board[nb] < R) return go ( quedan , R - 1 , nb );

	cortado += R;
	board[nb] -= R;
	rail[R]--;
	if( rail[R] == 0  && R == mini ){
		int a  = R;
		while(a < N && rail[a] == 0 ) a++;
		mini = a;
	}
	if( go ( quedan - 1 , R , nb ) ) return 1;
	mini = min( mini, R);
	rail[R]++;
	board[nb] += R;
	cortado -= R;
	
	
	if( go(quedan, R, nb+1) ) return 1;
	if( go( quedan, R-1, nb) ) return 1;
	return 0;
}
bool se_puede(int cant){
	int i,j ,k;
	memset(rail, 0, sizeof(rail));
	mx = -1; SUMA = 0;
	mini = INT_MAX;
	for(i = 0 ; i < cant;i++){
		rail[Rail[i]]++;
		SUMA += Rail[i];
		mx = max( mx, Rail[i]);
		mini = min(  mini, Rail[i] );
	}
	SB = 0; for(i = 0 ; i < numb ; i++) SB += board[i];
	if( SB < SUMA ) return 0;
	cortado = 0;
	return go(cant, mx, 0);
}
int main(){
	int i, j,k;
	fin = fopen("fence8.in", "r"); fout = fopen("fence8.out", "w");
	memset(rail, 0, sizeof(rail));
	fscanf(fin, "%i", &numb);
	for(i=0;i<numb;i++) fscanf(fin, "%i", &board[i]);
	fscanf(fin, "%i", &numr);int a;
	for(i=0;i<numr;i++){fscanf(fin, "%i", &a);if(a==0)continue;Rail.push_back(a);}
	sort(board, board+numb);
	sort(Rail.begin(), Rail.end());
	
	tot[numb] = 0;
	for(i = numb-1; i>=0;i--) tot[i] = tot[i+1] + board[i];
	
	for(int i = numr; i ; i-- ){
		printf("%i\n", i);
		if( se_puede(i) ){
			fprintf(fout, "%i\n", i);
			return 0;
		}
	}
	fprintf(fout, "%i\n", 0);
	return 0;
}
