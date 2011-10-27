#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <sstream>
#include <queue>
#include <algorithm>

#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>

#define forn(i, n) for(int i=0;i<int(n);i++)
#define FOR(i, a, b) for(int i=(a);i<int(b);i++)
#define RFOR(i, b, a) for(int i=(b);i>int(a);i--)
#define foreach(it, c)  for(__typeof((c).begin()) it = (c).begin();it!=(c).end();++it)
#define ALL(x)   (x).begin(),(x).end()
#define SIZE(x)   (int)(x).size()
#define SORT(x) sort(ALL(x))
using namespace std;
#define VI vector<int>
#define VS vector<string>
#define PB push_back
#define ISS istringstream
#define OSS ostringstream
typedef long long ll;
// NUNCA DEFINIR int max....
/* Max Flow */
# include <stdio.h>
# include <values.h>

# define MAXVERTICES 1802
# define Q MAXVERTICES+1

# define min(a,b) (((a)<(b))? (a):(b)) 
int rows, cols, p;
int n;
int f[MAXVERTICES][MAXVERTICES];
int cf[MAXVERTICES][MAXVERTICES];
int valor(int r, int c, int i){
	return (r*cols+c)*2+1+i;
}
vector<int> V;
int dx[5] = {-1, 0, 1, 0, 0};
int dy[5] = {0, 1, 0, -1, 0};
int adentro(int r, int c ){ if( r >= 0 && c >= 0 && r < rows && c < cols ) return 1; return 0;}
void setCapacity(void)
{
	memset(cf, 0, sizeof(cf));
	int i ,j ,k;
	vector<string> vec;
	string s;
	V.clear();
	for(i=0;i<rows;i++){
		cin >> s;
		vec.PB(s);
	}
	n = 2*rows*cols+1;
	
	for(i=0;i<rows;i++){
		for(j=0;j<cols;j++){
			if( vec[i][j] == '~' ) continue;
			if( vec[i][j] == '*' ){
				V.push_back(valor(i,j,0));
				cf[0][valor(i,j,0)] = 1;
				cf[valor(i,j,0)][valor(i,j,1)] = 1;
				for(k=0;k<4;k++){
					int r, c;
					r = dx[k]+i;
					c = dy[k]+j;
					if(!adentro(r,c))continue;
					if( vec[r][c] != '~' && vec[r][c] != '*'){
						cf[valor(i,j,1)][valor(r,c,0)] = 1;
					}
				}
			}else
			if( vec[i][j] == '@' ){
				cf[valor(i,j,0)][valor(i,j,1)] = 2000;
				for(k=0;k<4;k++){
					int r, c;
					r = dx[k]+i;
					c = dy[k]+j;
					if(!adentro(r,c))continue;
					if( vec[r][c] != '~' && vec[r][c] != '*'){
						cf[valor(i,j,1)][valor(r,c,0)] = 2000;
					}
				}
			}else
			if( vec[i][j] == '.' ){
				cf[valor(i,j,0)][valor(i,j,1)] = 1;
				for(k=0;k<4;k++){
					int r, c;
					r = dx[k]+i;
					c = dy[k]+j;
					if(!adentro(r,c))continue;
					if( vec[r][c] != '~' && vec[r][c] != '*'){
						cf[valor(i,j,1)][valor(r,c,0)] = 1;
					}
				}
			}else
			if( vec[i][j] == '#' ){
				cf[valor(i,j,0)][valor(i,j,1)] = 2000;
				cf[valor(i,j,1)][n] = p;
				for(k=0;k<4;k++){
					int r, c;
					r = dx[k]+i;
					c = dy[k]+j;
					if(!adentro(r,c))continue;
					if( vec[r][c] != '~' && vec[r][c] != '*'){
						cf[valor(i,j,1)][valor(r,c,0)] = 2000;
					}
				}
			}
		}
	}
	/* get input and make the graph */
	/* 0 : source   ,    n : sink */
}
void initialize(void)
{
	int i,j;
	for(i=0;i<=n;i++)
		for(j=0;j<=n;j++){
		f[i][j]=0;
		}
}
int augment(void)
{
	int q[Q],rear,front;
	int cost[MAXVERTICES],p[MAXVERTICES];
	int cfp,i,j;
	for(i=0;i<=n;i++)
		cost[i]=p[i]=-1;
	cost[0]=0;
	rear=front=0;
	q[rear++]=0;
	while(rear!=front){
		i=q[front++];
		if(front==Q) front=0;
		if(i==n) break;
		if( i != 0 ){
			int r, c;
			r = ((i-1)/2)/cols;
			c = ((i-1)/2)%cols;
			for(int k = 0 ; k< 5; k ++ ){
				int rr = r+dx[k];
				int cc = c+dy[k];
				for(int h=0;h<2;h++){
					int j = valor(rr,cc, h);
					if(cf[i][j]>0 && cost[j]==-1){
						cost[j]=cost[i]+1;
						p[j]=i;
						q[rear++]=j;
						if(rear==Q) rear=0;
					}
				}
			}
			int j = n;
			if(cf[i][j]>0 && cost[j]==-1){
				cost[j]=cost[i]+1;
				p[j]=i;
				q[rear++]=j;
				if(rear==Q) rear=0;
			}
			j = 0;
			if(cf[i][j]>0 && cost[j]==-1){
				cost[j]=cost[i]+1;
				p[j]=i;
				q[rear++]=j;
				if(rear==Q) rear=0;
			}
		}else{
			for(int h=0;h<V.size();h++){
				j = V[h];
				if(cf[i][j]>0 && cost[j]==-1){
					cost[j]=cost[i]+1;
					p[j]=i;
					q[rear++]=j;
					if(rear==Q) rear=0;
				}
			}
		}
	}
	if(cost[n]==-1) return 0;
	cfp=MAXINT;
	i=n;
	while(i){
		cfp=min(cfp,cf[p[i]][i]);
		i=p[i];
	}
	i=n;
	while(i){
		f[p[i]][i]+=cfp;
		f[i][p[i]]=-f[p[i]][i];
		cf[p[i]][i]-=cfp;
		cf[i][p[i]]+=cfp;
		i=p[i];
	}
	return 1;
}
int maxFlow(void)
{
	int i,totflow;
	setCapacity();
	initialize();
	while(augment());
	for(totflow=0,i=0;i<=n;i++)
		totflow+=f[0][i];
	return totflow;
}
int main(){
	int i,j ,k;
	while(scanf("%i %i %i", &rows, &cols, &p)!= EOF){
		printf("%i\n", maxFlow());
	}
	return 0;
}
