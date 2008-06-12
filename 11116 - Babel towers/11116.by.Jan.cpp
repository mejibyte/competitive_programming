/*
   Author       :   Jan
   Problem Name :   Babel Towers
   Algorithm    :   Math, Center of Masses
   Complexity   :   O(n^2)
*/

#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>

using namespace std;

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

#define CLR(a) memset(a,0,sizeof(a))

#define MAX 1001
const double eps = 1e-7;

int n;
double sumMass[MAX],sumX[MAX],sumY[MAX];

struct circle
{
   double x,y,r;
}C[MAX];

bool input()
{
   scanf("%d",&n);
   if(!n) return false;
   for(int i=1;i<=n;i++)
   {
      scanf("%lf %lf %lf",&C[i].x,&C[i].y,&C[i].r);
      sumX[i]=sumX[i-1]+C[i].x*C[i].r*C[i].r;
      sumY[i]=sumY[i-1]+C[i].y*C[i].r*C[i].r;
      sumMass[i]=sumMass[i-1]+C[i].r*C[i].r;
   }
   return true;
}

void process()
{
   int i,j;
   double sX,sY,sM,X,Y;

   for(i=1;i<=n;i++)
   {
      for(j=i-1;j>=1;j--)
      {
         sM=sumMass[i]-sumMass[j];
         sX=sumX[i]-sumX[j];
         sY=sumY[i]-sumY[j];
         X=sX/sM;
         Y=sY/sM;
         if((X-C[j].x)*(X-C[j].x)+(Y-C[j].y)*(Y-C[j].y)+eps>C[j].r*C[j].r)
            break;
      }
      if(j) break;
   }
   if(i==n+1) puts("Feasible");
   else printf("Unfeasible %d\n",i-1);
}

int main()
{
   while(input())
   {
      process();
   }
   return 0;
}
