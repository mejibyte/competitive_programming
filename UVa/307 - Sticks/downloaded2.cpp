#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
int a[100],n,m,ans;
int maxx,minn;
bool flag;
void dfs (int x, int s, int len, int st) // need to find the sum of the number of stitching need to find how much the maximum value of the root
{
         if (! x) // looking over
    {
        ans=len;
        flag=true;
    }
    if(flag)
        return;
         if (s == len) // find a wooden stick
    {
        dfs(x-1,0,len,maxx);
        return;
    }
    for(int i=st;i>=minn;i--)
    {
        if(a[i]&&s+i<=len)
        {
            a[i]--;
            dfs(x,s+i,len,i);
            a[i]++;
            if(!s)
                break;
        }
    }
}
int main()
{
    while(~scanf("%d",&n))
    {
        if(n==0)
            break;
        int sum=0;
        memset(a,0,sizeof(a));
        maxx=0,minn=1000,flag=0;
        for(int i=1;i<=n;i++)
        {
            int x;
            scanf("%d",&x);
            if(x>50)
                continue;
                         a [x] ++; // there have been several
            sum+=x;
            if(x>maxx)
                maxx=x;
            if(x<minn)
                minn=x;
        }
                 for (int i = maxx; i <= sum; i ++) // for each sequence and the maximum number of all the values ​​and is convenient to find the minimum required length of the stick
        {
            if(sum%i==0)
                                 dfs (sum / i, 0, i, maxx); // i need to find the length of the stick sum / i root of the current required length up sticks splice splice splice length of the stick section i
            if(flag)
                break;
        }
        printf("%d\n",ans);
    }
    return 0 ;
}