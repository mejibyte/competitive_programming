#include <stdio.h>

int main(){
  char c;
  short b = 1;
  while ((c = getchar()) != EOF){
    if (c == '"'){
      printf(b?"``":"''");
      b = !b;
    }else
      putchar(c);
  }
  return 0;
}
