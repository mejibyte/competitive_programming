#include<iostream>

using namespace std;

int n,CASO,T[100],mem[55][55][55][40],INF;

int dp(int a, int b, int c, int voy)
{
    if(a>51||b>51||c>51)
        return 1<<30;

    if(voy==n)
        return max(a,max(b,c));

    if(mem[a][b][c][voy]!=INF)
       return mem[a][b][c][voy];

    int na,nb,nc,mimin,s=1<<30;

    na=a,nb=b,nc=c;
    na+=T[voy];
    mimin=min(na,min(nb,nc));
    s<?=dp(na-mimin,nb-mimin,nc-mimin,voy+1);

    na=a,nb=b,nc=c;
    nb+=T[voy];
    mimin=min(na,min(nb,nc));
    s<?=dp(na-mimin,nb-mimin,nc-mimin,voy+1);

    na=a,nb=b,nc=c;
    nc+=T[voy];
    mimin=min(na,min(nb,nc));
    s<?=dp(na-mimin,nb-mimin,nc-mimin,voy+1);

    return mem[a][b][c][voy]=s;
}

int main()
{
    cin>>CASO;

    for(int i=1;i<=CASO;i++)
    {
        cin>>n;

        for(int j=0;j<n;j++)
            cin>>T[j];

        memset(mem,-1,sizeof(mem));
        INF=mem[0][0][0][0];

        printf("Case %d: %d\n", i, dp(0,0,0,0));
    }

    return 0;
}
