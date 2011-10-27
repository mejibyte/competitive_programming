#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
struct elefante{
  int w,a,i;
  elefante(int W, int A, int I) : w(W), a(A), i(I){}
  bool operator < (const elefante& x) const{
    return (w < x.w) || (w == x.w && a < x.a) ||
      (w == x.w && a == x.a && i < x.i);
  }
};
void print(const int &i,const vector<int> &p,const vector<elefante> &e){
  if(p[i]==-1){
    cout<<e[i].i<<endl;
  }else{
    print(p[i],p,e);
    cout<<e[i].i<<endl;
  }
}
int main(){
  int w, a;
  int cuenta=1;
  vector <elefante> e;
  while(cin >> w >> a){
    e.push_back(elefante(w,a,cuenta++));
  }
  sort(e.begin(),e.end());
  vector <int> A (e.size(),1),P(e.size(),-1);
  for(int i=1;i<e.size();++i){
    for(int j=0;j<i;++j){
      if(e[j].a>e[i].a && A[i]< A[j]+1){
	A[i]=A[j]+1;
	P[i]=j;
      }
    }
  }
  int maximo=A[0];
  int indexMax=0;
  for(int i=1;i<A.size();++i){
    if(A[i]>maximo){
      maximo=A[i];
      indexMax=i;
    }
  }
  cout<<maximo<<endl;
  print(indexMax,P,e);
  return 0;
}
