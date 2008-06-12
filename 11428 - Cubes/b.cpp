#include<iostream>
#include<math.h>
using namespace std;
int main(){
  int n;
  while(cin>>n &&n){
    double aux=(1.+sqrt(1.+(8.*sqrt((double)(n)))))/2;
    aux=floor(aux);
    
    if(n==(aux*aux*aux-(aux-1)*(aux-1)*(aux-1))){
      cout<<aux<<" "<<aux-1;
    }else{
      int i=1;
      while(i*i*i <= (n+1)){
	++i;
      }
      --i;
      //    cout << i << endl;
      if (i*i*i == n+1){
	cout << i << " 1";
      } else{
	cout<<"No solution";
      }
    }
    cout<<endl;
  }
}
