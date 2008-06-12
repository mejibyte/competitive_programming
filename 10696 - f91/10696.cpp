/*
  Accepted
 */
#include <stdio.h>

int f[1000001];

int main(int argc, char const *argv){
  for (int i = 1000000; i > 100; --i){
    f[i] = i-10;
  }
  for (int i = 100; i > 0; --i){
    f[i] = f[f[i+11]];
  }

  int n;
  while (scanf("%d", &n) == 1 && n){
    printf("f91(%d) = %d\n", n, f[n]);
  }

  return 0;
}
