#include<cstdio>
#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#include<vector>
using namespace std;
int n,m;
bool mycomparasion(int a,int b)
{
    if(a%m==b%m)
    {
        if(abs(a)%2 == abs(b)%2)
            if(abs(a)%2==1)
                if(a>b)
                    return true;
                else
                    return false;
            else
                if(a>b)
                    return false;
                else
                    return true;
        else
            if(abs(a)%2==1 && abs(b)%2==0)
                return true;
            else
                return false;

    }
    return a%m<b%m;

}

#define forn(i,a,b) for(int i=a;i<b;i++)

int main()
{
    //freopen("in.txt","r",stdin);
    while(scanf("%d %d",&n,&m)==2 && n && m)
    {
        vector<int>d;
        forn(i,0,n)
        {
            int k;
            scanf("%d",&k);
            d.push_back(k);
        }
        printf("%d %d\n",n,m);
        sort(d.begin(),d.end(),mycomparasion);
        forn(i,0,n)
        printf("%d\n",d[i]);
    }
    printf("0 0\n");
    return 0;
}
