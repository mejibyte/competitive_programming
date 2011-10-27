#include<sstream>
#include<iostream>
#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<vector>
#include<map>
#include<string>
#define MAX(a,b) a>b?a:b
#define toPAngle(angle) angle>0?angle:(angle+pi)
#define D(X) cerr<<__LINE__<<" "<<#X<<" "<<x<<endl
const double pi=acos(-1);
using namespace std;

struct point{
  double x,y;
  point(){}
  point(string a){
    stringstream t(a);
    t>>x>>y;
    //    D(x),D(y);
  }
  bool operator <(const point &t)const{
    return x<t.x||(x==t.x &&y<t.y);
  }
};
int main(){
  int cases;
  scanf("%d",&cases);
  string aux;
  getline(cin,aux);
  getline(cin,aux);
  for(int ans;cases-- && cin.peek()!=EOF;printf("%d\n",ans),cases<=0?:printf("\n")){
    vector<point> p;
    ans=2;
    for(string dum;getline(cin,dum) && dum!="";p.push_back(point(dum)));
    if(p.size()<3)continue;
    sort(p.begin(),p.end());
    double m;
    for(int i=0;i<p.size()-1;++i){
      map<double,int> angles;
      for(int j=i+1;j<p.size();++j){
        m=toPAngle(atan2(p[i].y-p[j].y,p[i].x-p[j].x));
        if(angles.count(m))
          ++angles[m];
        else
          angles[m]=2;
        printf("%lf between (%lf, %lf) and (%lf, %lf), angles[m] = %d\n", m, p[i].x, p[i].y,
               p[j].x, p[j].y, angles[m]);
        ans=MAX(angles[m],ans);
      }
    }
  }
  return 0;
}
