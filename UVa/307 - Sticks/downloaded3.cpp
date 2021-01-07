// https://www.programmersought.com/article/99102704769/

#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 64;

int l[N+20],n,sum,now,vis[N+20];

bool dfs(int pre,int need,int rest){
    if (rest==0) return true;

    for (int i = pre;i <= n;i++)
        if (!vis[i] && l[i]<=need){
            vis[i] = 1;
            if (l[i]==need && dfs(1,now,rest-l[i]))
                return true;
            else if ( dfs(i+1,need-l[i],rest-l[i]))
                    return true;
            vis[i] = 0;
            if (rest==sum) return false;
            if (need==now) return false;
            while (i+1<=n && l[i+1]==l[i]) i++;
        }

    return false;
}

int main(){
    //freopen("F:\\rush.txt","r",stdin);
    while (~scanf("%d",&n)){
        if (n==0) break;
        sum = 0;
        for (int i = 1;i <= n;i++)
            scanf("%d",&l[i]),sum+=l[i];
        for (int i = 1;i <= n;i++) vis[i] = 0;
        sort(l+1,l+1+n);
        reverse(l+1,l+1+n);
        int ans = sum;
        for (now = l[1];now < sum;now++)
            if (sum%now==0){
                if (dfs(1,now,sum)){
                    ans = now;
                    //printf("%d\n",now);
                    break;
                }
            }
        printf("%d\n",ans);
    }
    return 0;
}