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
#define REP(i, n) for(int i=0;i<int(n);i++)
#define foreach(it, c)  for(typeof((c).begin()) it = (c).begin();it!=(c).end();++it)
#define ALL(x)   (x).begin(),(x).end()
#define SORT(x) sort(ALL(x))
using namespace std;
#define VI vector<int>
#define VS vector<string>
#define PB push_back
#define ll long long
#define VP vector<pair<int,int> > 
template <typename T> void enqueue(vector< T > &H, T par){
	H.PB(par);
	int e = H.size() -1 ;
	while(e != 1  && par < H[e/2] ){
		swap(H[e], H[e/2]);
		e /= 2;
	}
}
template <typename T> void dequeue(vector< T > &H){
	if( H.size() == 1 ) return;
	int f = 1;
	int e = H.size() -1 ;
	swap(H[f], H[e]);
	H.pop_back();
	e --;
	while(1){
		int d = f*2;
		if( d > e ) break;
		if( d+1 <= e && H[d] > H[d+1] ) d++;
		if( H[d] > H[f] ) break;
		swap(H[f], H[d]);
		f = d;
	}
}


int main(){
	int i,j ,k;
	
	int aux;string s;
	vector<int> H1;
	vector<pair<int,int > > H2;
	H1.PB(10000000); // DUMMY
	for(i=1;i<30001;i++)enqueue(H1,i);
	H2.PB(make_pair(1000000, 1234114));
	int ultima[30010];
	REP(i, 30010) ultima[i] = -1000;
	while(cin >> aux){
		cin >> s;
		if( s == "." ){
			int c ; cin >> c;
			if( aux - 600 < ultima[c] ){
				printf("+\n");
				ultima[c] = aux;
			}else{
				printf("-\n");
			}
		}else{
			while(H2.size() > 1){
				int t = H2[1].first;
				int c = H2[1].second;
				if( t < ultima[c] ){
					dequeue(H2);
					enqueue(H2, make_pair(ultima[c], c));
				}else{
					if( aux - 600 >= ultima[c] ){
						dequeue(H2);
						enqueue(H1, c);
					}else break;
				}
			}
			int r = H1[1];
			printf("%i\n", r);
			dequeue(H1);
			enqueue(H2, make_pair(aux, r));
			ultima[r] = aux;
			
		}
	}return 0;
}
