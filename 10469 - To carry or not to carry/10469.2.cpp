#include <stdio.h>

int main(){
  unsigned int x,y;
  while (scanf("%u %u", &x, &y) == 2){
    printf("%u\n", x ^ y);
  }
  return 0;
}
