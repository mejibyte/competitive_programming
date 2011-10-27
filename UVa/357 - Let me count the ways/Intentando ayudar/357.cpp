/*
  Accepted
 */
#include <stdio.h>
#define MAX 30000
long long ways[MAX+1];
int coin[5] = { 50,25,10,5,1 };

int main()
{

    int i,j,n,c;
    for(i=1; i<=MAX; i++) ways[i] = 0;
    ways[0] = 1;
    for (i=0; i<5; i++)
   {
        c = coin[i];
        for (j=c; j<=MAX; j++)
            ways[j] += ways[j-c];
    }
   while(scanf("%d",&n) == 1)
   {
     if (ways[n] == 1)
       printf("There is only 1 way to produce %d cents change.\n", n);
     else
       printf("There are %lld ways to produce %d cents change.\n",ways[n],n);
   }
   return 0;
}
