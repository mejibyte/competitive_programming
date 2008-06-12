#include <stdio.h>

int main(){
  char c;
  bool b = true;
  while ((c = getchar()) != EOF){
    if (c == '"'){
      printf(b?"``":"''");
      b = !b;
    }else
      putchar(c);
  }
  return 0;
}
