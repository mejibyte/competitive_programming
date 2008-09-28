//Robado de http://acm.uva.es/board/viewtopic.php?f=42&t=42314&sid=0cfc4d6e55802e83ea57fed814183ab6
#include<stdio.h>
#include<string.h>

#define SZ 105

long long dp[10][SZ] , ret , cnt[SZ];

int main(){
   //freopen("e.in" , "r" , stdin);
   //freopen("e.out" , "w" , stdout);
   long long n , i , x , j , sm;
   double p;
   while(scanf("%lld" , &n) == 1 && n){
      memset(cnt , 0 , sizeof(cnt));
      sm = 75;
      for(i = 0;i<n;i++){
         scanf("%lf" , &p);
         x = (long long)(p*10 + .5);
         cnt[i] = x%10;
      }
      ret = 0;
      memset(dp , 0 , sizeof(dp));
      for(i = 0;i<n;i++)
         dp[0][cnt[i]] ++;
      for(i = 1;i<7;i++)
         for(j = 0;j<n;j++)
            for(x = sm;x>=cnt[j];x--)
               dp[i][x] += dp[i-1][x-cnt[j]];
      for(i = 0;i<n;i++){
         for(j = 0;j<=sm;j++)
            if(dp[6][j])
               ret += (((j+cnt[i])/10)*dp[6][j]);
      }
      printf("%lld\n" , ret);
   }
   return 0;
}
