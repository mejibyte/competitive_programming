#include<stdio.h>
#include<string.h>
#define MAX 106

#define WHITE 0
#define GRAY 1
#define BLACK 2

int a[MAX][MAX], n;
int color[MAX], d[MAX], low[MAX], pre[MAX], used[MAX];

char AP[MAX][33];
int apN;

char city[MAX][33];

int  time;

void init()
{
   int i, j;
   for(i=0; i<n; i++)
   {
      color[i]=0;      
      pre[i]=-1;
      used[i]=0;
   }
   for(i=0; i<n; i++)
      for(j=0; j<n; j++)
         a[i][j]=0;
}

void DFS_Visit(int u)
{
   color[u] = GRAY;
   time = time+1;
   d[u] = time;
   low[u]=time;
   int gr=-1, i, fl=0;
   for(i=0; i<n; i++)
      if(a[u][i]==1)
      {   
        if(color[i] == WHITE)
        {         
           pre[i]=u;
           a[i][u]=0;
          DFS_Visit(i);
         
          fl++;
          if(pre[u]==-1)
          {
             if(fl==2 && used[u]==0)
             {
                used[u]=1;
               strcpy(AP[apN], city[u]);
               apN++;            
               continue;
             }
          }
          else if(low[i]>=d[u] && used[u]==0)
          {
             used[u]=1;
             strcpy(AP[apN], city[u]);
             apN++;            
          }
          else if(low[i]<low[u])
          {      
             low[u]=low[i];         
          }
        }
        else if(color[i]==GRAY)
        {
           if(d[i]<low[u])
              low[u]=d[i];
        }
        else if(color[i]==BLACK)
        {
           if(low[i]<low[u])
              low[u]=low[i];
        }
       }
   
   color[u] = BLACK;
   time = time+1;
}


int fndL(char *s)
{
   int i;
   for(i=0; i<n; i++)
      if(strcmp(city[i], s)==0)
         return i;
}


int main()
{
  //freopen("in.txt", "r", stdin);
   int test=0,  i, j, x, y,m, v;
   char s1[33], s2[33], tmp[33];
   
   while(scanf("%d", &n)==1 && n)
   {   
      for(i=0; i<n; i++)
         scanf("%s", city[i]);

      scanf("%d", &m);
      init();
      for(i=0; i<m; i++)
      {
         scanf("%s %s", &s1, &s2);
         x=fndL(s1);
         y=fndL(s2);
         a[x][y]=1;
         a[y][x]=1;
      }
      apN=0;      
      time=0;
      for(i=0; i<n; i++)
         DFS_Visit(i);
      if(test)
         puts("");
      printf("City map #%d: %d camera(s) found\n", test+1, apN);
      test++;
      for(i=0; i<apN; i++)
         for(j=i+1; j<apN; j++)
            if(strcmp(AP[i], AP[j])>0)
            {
               strcpy(tmp, AP[i]);
               strcpy(AP[i], AP[j]);
               strcpy(AP[j], tmp);
            }
      for(i=0; i<apN; i++)
         printf("%s\n", AP[i]);

   }
   return 0;
} 
