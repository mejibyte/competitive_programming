#include<cstdio>
#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#include<vector>
using namespace std;
int n,m;

#define D(x) cout << #x " = " << (x) << endl

int mod2(int x) {
    return (x % 2 + 2) % 2;
}

bool compare(int a,int b) {
    if (a % m != b % m) return a % m < b % m;
    if (mod2(a) != mod2(b)) return mod2(a) == 1;
    if (mod2(a) == 0) return a < b;
    return a > b;
}

#define forn(i,a,b) for(int i=a;i<b;i++)

int main()
{
//    freopen("in.txt","r",stdin);
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
        sort(d.begin(),d.end(),compare);
        forn(i,0,n)
        printf("%d\n",d[i]);
    }
    printf("0 0\n");
    return 0;
}
