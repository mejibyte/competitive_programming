#include<iostream>
#include<queue>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
#include<string>
#include<cstring>
#include<map>
#include<numeric>
#include<sstream>
#include<cmath>
using namespace std;
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define pb push_back
#define f(i,x,y) for(int i = x; i<y; i++ )
#define FOR(it,A) for(typeof A.begin() it = A.begin(); it!= A.end(); it++)
#define quad(x) (x) * (x)
#define mp make_pair
#define clr(x, y) memset(x, y, sizeof x)
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef long long ll;
typedef long double ld;
#define inf (1 << 30)
int m;
int tam;
string to;
ll mod=4207849484LL;

#define MAX 103
ll C[MAX+5][MAX+5];

//map<ll,bool> esta[MAX+5];
int esta[10000010];
int main(){
    clr(esta,-1);
    esta[1]=1;
    for(int i = 0; i < MAX; i++){ C[i][i] = C[i][0] = 1;}
    
    for(int i = 1; i < MAX; i++) for(int j = 1; j < i; j++){    
        C[i][j] = C[i-1][j-1] + C[i-1][j] ;
        if(C[i][j]<10000009 && C[i][j]>=0 && esta[ C[i][j] ]==-1)
            esta[C[i][j]]=i;
    }
    
    
    f(i,1,10000008)if(esta[i]==-1)esta[i]=i;
    
    //cout<<C[50][0]<<endl;
    //cout<<"sd"<<endl;
    
    int casos;
    cin>>casos;
    ll S;
    f(cc,1,casos+1){
        int r=-1;
        cin>>S;
        ll A,B;
        int nn,mm;
        for(ll i=1;i*i<=S;i++){
            if(S%i==0){
               A=i;
               B=S/i;
               nn=esta[A];
               mm=esta[B];
               
               //cout<<nn<<" "<<mm<<" dd "<<A<<" "<<B<<endl;
               if(nn!=-1 && mm!=-1){
                    if(r==-1 or nn+mm < r)
                        r=nn+mm;
               }
            }
        }
       
        cout<<"Case #"<<cc<<": "<<r<<endl;
    }
}
