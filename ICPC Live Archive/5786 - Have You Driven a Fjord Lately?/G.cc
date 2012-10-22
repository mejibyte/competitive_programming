
#include <cmath>
#include <stdio.h>
#include <iostream>
using namespace std;


const bool DEBUG=false;
#define FOR(a,n) for(int a=0;a<n;a++)

struct Fjordtype{
long long p1x, p1y, p2x,p2y, p3x,  p3y;
long long v1x, v1y, v2x,  v2y;
double v1len, v2len;
double theta;
double a;                   // = 1/2*sin(theta/2) = distance up the sides for len 1 bridge
double savings;             // = 1/sin(theta/2) - 1
double opening;             // dist from p1 to p3
};

int CaseNo=1;
Fjordtype fjords[50];
int n,  m;
double Save[50][5001];
double D[50][5001];

double dist(double a1,  double a2, double b1,  double b2){
  return sqrt((a1-a2)*(a1-a2)+(b1-b2)*(b1-b2));
}

void getFjords(){
  int a,b;
  double dot;
  
  cin>>a>>b;
  FOR(i,n){           //get info for the ith fjord
    fjords[i].p1x=a; fjords[i].p1y=b;
    cin>>fjords[i].p2x>>fjords[i].p2y;
    cin>>a>>b;    
    fjords[i].p3x=a; fjords[i].p3y=b;

    //calculate vec1 and vec2
    fjords[i].v1x = fjords[i].p1x  - fjords[i].p2x;
    fjords[i].v1y = fjords[i].p1y  - fjords[i].p2y;
    fjords[i].v2x = fjords[i].p3x  - fjords[i].p2x;
    fjords[i].v2y = fjords[i].p3y  - fjords[i].p2y;
    fjords[i].v1len = sqrt(fjords[i].v1x*fjords[i].v1x +  fjords[i].v1y*fjords[i].v1y);
    fjords[i].v2len = sqrt(fjords[i].v2x*fjords[i].v2x +  fjords[i].v2y*fjords[i].v2y);
    dot = fjords[i].v1x*fjords[i].v2x + fjords[i].v1y*fjords[i].v2y;
    fjords[i].theta =acos(dot/(fjords[i].v1len* fjords[i].v2len));
    fjords[i].a = 1/(2*sin(fjords[i].theta/2)); 
    fjords[i].savings = 1/(sin(fjords[i].theta/2))-1;
    fjords[i].opening = dist(fjords[i].p1x,fjords[i].p3x,fjords[i].p1y,fjords[i].p3y);
  }
}

void makeSavingsTable(){  //Save[i][j] = savings  if build bridge of length j over fjord i
  double  dot, mag, projx, projy;   //(projx,projy)= point of projection
                                    //mag = magnitude of proj
                                    //dot = v1 dot v2
  double perp, len;                 //perp = perp distance
  int b;                            //b = length of bridge
  double d, p4x, p4y, e, p;

  FOR(i,n){   //build Save[k][]
    FOR(j,m+1) Save[i][j]=-1;
    Save[i][0]=0;
    //v1 is shorter than v2
    if (fjords[i].v1len<=fjords[i].v2len){
      //project v1 onto v2
      dot = fjords[i].v1x*fjords[i].v2x+fjords[i].v1y*fjords[i].v2y;
      mag = dot/(fjords[i].v2len*fjords[i].v2len); 
      projx = fjords[i].p2x + mag*fjords[i].v2x;  //(projx,projy) on v2
      projy = fjords[i].p2y + mag*fjords[i].v2y;
      perp = dist(fjords[i].p1x,projx,fjords[i].p1y,projy);
      
      // now build the bridges not from p1 (= short bridges)
      len = fjords[i].a;
      b =1;
      while (len<=fjords[i].v1len && b <= m) {
        Save[i][b] = Save[i][b-1] + fjords[i].savings;
        b++;
        len +=  fjords[i].a;
      }
      if(b<=m){
      //now bridges starting at p1 over to v2
      while (b<=fjords[i].opening && b<=m){
        d  = sqrt(b*b - perp*perp);
        d += mag*fjords[i].v2len;       //this is dist down v2 the bridge lands
        Save[i][b] = fjords[i].v1len + d - b; 
        b++;
      }
      //finally bridge of length b from p3  to v1 (b > opening) 
      // project v2 to v1, point of projection is p4
      // rt triangle p4 to p3 to v1 with hyp = b, find length of side on v1 (= e)
      // length on v1 is len of proj - e
      mag = dot/(fjords[i].v1len * fjords[i].v1len);
      p4x = fjords[i].p2x + mag*fjords[i].v1x;
      p4y = fjords[i].p2y + mag*fjords[i].v1y;
      d = dist(fjords[i].p3x, p4x, fjords[i].p3y, p4y);     //d = dist of perp
      e = sqrt(b*b-d*d);
      p = dist(p4x, fjords[i].p2x, p4y, fjords[i].p2y) - e;
      Save[i][b] = p + fjords[i].v2len - b;
      b++;
     }
     //finish out Save[i][]
     while(b<=m)
       Save[i][b++]=-1;
    }
    else {      // v2 shorter than v1
      //project v2 onto v1
      dot = fjords[i].v1x*fjords[i].v2x+fjords[i].v1y*fjords[i].v2y;
      mag = dot/(fjords[i].v1len*fjords[i].v1len);  
      projx = fjords[i].p2x + mag*fjords[i].v1x;  //(projx,projy) on v2
      projy = fjords[i].p2y + mag*fjords[i].v1y;
      perp = dist(fjords[i].p3x,projx,fjords[i].p3y,projy);
      
      // now build the bridges not from p1 (= short bridges)
      len = fjords[i].a;
      b =1;
      while (len<=fjords[i].v2len && b <= m) {
        Save[i][b] = Save[i][b-1] + fjords[i].savings;
        b++;
        len +=  fjords[i].a;
      }
      if(b<=m){
      //now bridges starting at p3 over to v1
      while (b<=fjords[i].opening && b<=m){
        d  = sqrt(b*b - perp*perp);
        d += mag*fjords[i].v1len;       //this is dist down v1 the bridge lands
        Save[i][b] = fjords[i].v2len + d - b; 
        b++;
      }
      //finally, distance b from p1  to v2 (b > opening)
      mag = dot/(fjords[i].v2len * fjords[i].v2len);
      p4x = fjords[i].p2x + mag*fjords[i].v2x;
      p4y = fjords[i].p2y + mag*fjords[i].v2y;
      d = dist(fjords[i].p1x, p4x, fjords[i].p1y, p4y);     //d = dist of perp
      e = sqrt(b*b-d*d);
      p = dist(p4x, fjords[i].p2x, p4y, fjords[i].p2y) - e;
      Save[i][b] = p + fjords[i].v1len - b;
      
      b++;
     }
     //finish out Save[i][]
     while(b<=m)
       Save[i][b++]=-1;
    }
  }
}

void findBest(){
  //D[i][j] = best savings using j bridge ver fjords 0..i
  int bridge, bestbridge;
  double best;

  FOR(i,n)              //init D[][]
    FOR(j,m+1)
      D[i][j]=-1;
  //fill in 0th row (use only bridge 0)
  FOR(k,m+1)  D[0][k] = Save[0][k];    
  
  for(int i=1;i<n;i++) 
    for(int j=0;j<=m;j++) {  // compute D[i][j] 
      bridge = 0;    //= length of span over fjord i (can't use more than j)
      while (bridge <= j && Save[i][bridge] >-1) {
        if(Save[i][bridge] + D[i-1][j-bridge] > D[i][j] && D[i-1][j-bridge]>-1)
          D[i][j] = Save[i][bridge] + D[i-1][j-bridge];      //better savings
        bridge++;
    } 
  }
  //find best  savings (on D[n-1][])
  best = D[n-1][m];  bestbridge = m;
  FOR(k,m) 
    if(D[n-1][k] > best){
      best = D[n-1][k];
      bestbridge = k;
    }
  printf("Case %d: %d meters used saving %4.2f meters\n",CaseNo,bestbridge,best);
  CaseNo++;
}


void PrintPoints(){
  FOR(i,n){
   cout<<fjords[i].p1x<<' '<<fjords[i].p1y<<' ';
   cout<<fjords[i].p2x<<' '<<fjords[i].p2y<<' ';
   cout<<fjords[i].p3x<<' '<<fjords[i].p3y<<endl;
  }
}

void PrintSaveTable(){
  cout<<"Save table:"<<endl;
  FOR(k,n){
    FOR(j,m+1) cout<<Save[k][j]<<' ';
    cout<<endl;
  }


}

int main(){

  cin>>n>>m;

  while (n>0){
    getFjords();
    makeSavingsTable();
    findBest();          //uses DP on the SaveTable

    cin>>n>>m;
  }
  return 0;
}
