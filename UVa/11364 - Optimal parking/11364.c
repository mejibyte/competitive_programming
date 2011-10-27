#include <stdio.h>
#include <stdlib.h>
int less(const void*a, const void*b){return*(short*)(a)-*(short*)(b);}
int main(){
  short i, c, a[20], n;
  for (scanf("%hd", &c); c--; printf("%hd\n", 2*(a[n-1]-a[0]))){
    for (scanf("%hd", &n), i=0; i<n; scanf("%hd", &a[i++]));
    qsort(a, n, sizeof(short), less);
  }
  return 0;
}
