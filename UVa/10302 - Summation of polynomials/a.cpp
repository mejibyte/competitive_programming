/* 
   Sebastian Arcila Valenzuela
   sebastianarcila@gmail.com
   2009
   @(#)TEMPLATE.c.tpl
 */
#include <stdio.h>
typedef unsigned long long ull;
int main()
{
  for(ull x,ans;scanf("%llu",&x) == 1; printf("%llu\n",ans*ans))
    if((x&1))
      ans = (x+1)/2*x;
    else
      ans = x/2*(x+1);
      
  return 0;
}

