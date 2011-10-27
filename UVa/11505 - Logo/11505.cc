#include <iostream>
#include<math.h>
#include<stdio.h>
#include<assert.h>
#include<string>
using namespace std;
const double pi=acos(-1);
inline double toRad(const double anl){
  return anl*pi/180.0;
}
int main(){
  int cases;
  cin>>cases;
  for(int n;cases-- &&cin>>n;){
    double t,x=0,y=0,teta=0;
    for(string ins;n-- && cin>>ins>>t;){
      if(ins=="fd"){
	x+=t*cos(teta);
	y+=t*sin(teta);
      }else if(ins=="bk"){
	x-=t*cos(teta);
	y-=t*sin(teta);
      }else if(ins=="lt"){
	teta+=toRad(t);
      }else if(ins=="rt"){
	teta-=toRad(t);
      }else{
	assert(false);
      }
    }
    printf("%.0lf\n",sqrt(x*x+y*y));
  }
  return 0;
}
