#include<iostream>
#include<math.h>
using namespace std;
typedef unsigned long long ull;
int main(){
  ull n,x,y;
  while(cin>>n && n){
    ull aux=n/2;
    for(ull k=1;k<=n/2;++k){
      // cout<<aux<<" "<<k<<endl;
      x=0;
      y=0;
      if(n%k==0){
	
	if (sqrt(12*n/k - 3*k*k) < 3*k){
	  continue;
	}

	y = (sqrt(12*n/k -3*k*k)-3*k)/6;
	x=y+k;
	//	cout<<x<<" "<<y<<"afuera\n";
	if(n==x*x*x-y*y*y){
	  cout<<x<<" "<<y<<" "<<k;
	  break;
	}
	//	if(k==9)cout<<x<<" "<<y<<" este y"<<(    -3*k + sqrt( 12*n / k - 3*k*k  )   )  / 6.<<endl;
	if(k!=2) aux=aux/k;
      }

    }
    cout << "sali\n";
    if(n!=x*x*x-y*y*y){
      cout<<"No solution";
    }
    
    cout<<endl;
  }
  return 0;
}
