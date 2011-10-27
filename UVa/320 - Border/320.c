#include <stdio.h>
#include <string.h>
char m[32][32], d, x = 'X';
int main(){
  int t=1, c, i, j;
  for (scanf("%d", &c); c-- && scanf("%d %d\n", &j, &i) == 2 && printf("Bitmap #%d\n", t++); printf("\n")){
    memset(m, '.', sizeof m);
    while (scanf("%c", &c) && c != '.'){
      if (c == 'E') m[i-1][j++] = x;
      else if (c == 'W') m[i][(j--)-1] = x;
      else if (c == 'S') m[(i--)-1][j-1] = x;
      else if (c == 'N') m[i++][j] = x;
    }
    for (i=31; i>=0; --i, printf("\n"))
      for (j=0; j<32; printf("%c", m[i][j++]));
  }
  return 0;
}
