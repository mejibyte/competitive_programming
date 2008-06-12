#include <stdio.h>


int main(){
  int f[10001];
  f[1] = 1;
  for (int i = 2; i <= 10000; ++i){
    f[i] = f[i-1]*i;
    while (f[i]%10 == 0) f[i] /= 10;
    f[i] %= 100000;
    //printf("f[%d] es %d\n", i, f[i]);
  }

  int n;
  while (scanf("%d", &n) == 1){
    printf("%5d -> %d\n", n, f[n]%10);
  }
  return 0;
}
