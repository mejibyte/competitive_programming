/*

 */
#include <stdio.h>

int main(){
  int n;
  while (scanf("%d", &n) == 1 && n){
    printf("f91(%d) = %d\n", n, (n<=101?91:n-10));
  }

  return 0;
}
