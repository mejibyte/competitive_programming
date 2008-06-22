#include <cstdio>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <sstream>
#include <cstdlib>
#include <stack>
#include <queue>
#define FOR(i,j,n) for (int i=j;i<n;++i)
#define FORI(i,j,n) for (int i=j;i<=n;++i)
#define FORN(i,n) FOR(i,0,n)
#define sz size()
#define foreach(i, c) for( __typeof( (c).begin() ) i = (c).begin(); i != (c).end(); ++i )
#define CPRESENT(container, element) (find(ALL(container),element) != container.end())
#define MIN(a,b) (a < b ? a : b)
#define MAX(a,b) (a > b ? a : b)
#define ALL(x) x.begin(), x.end()
#define PB push_back
#define INF 1<<30

using namespace std;
int b,c,e,d,n;

int t[100][100];
int main(){
  cin>>n;

  while(n--){

    memset(t,0,sizeof(t));
    for (int i=0;i<9;i+=2){
      for (int j=0;j<(i/2)+1;j++){
        cin>>t[i][2*j];
      }
    }

    for (int i=2;i<9;i+=2){
      for (int j=1,num=0;num<i/2;num++,j+=2){
        t[i][j]=(t[i-2][j-1]-t[i][j-1]-t[i][j+1])/2;
      }
    }

    for (int i=1;i<9;i+=2){
      for (int j=0;j<=i;j++){
        t[i][j]=t[i+1][j]+t[i+1][j+1];
      }
    }

    FORN(i,9){
      bool entre=0;
      FORN(j,i+1){
        if (entre)  cout<<" ";
        entre=1;
        cout<<t[i][j];
      }
      cout<<endl;
    }


  }
  return 0;
}

