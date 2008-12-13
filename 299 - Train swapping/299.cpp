#include <algorithm>
#include <stdio.h>
int tren[50], c, l, i, j, r;

int bubblesort(){
  for (r=0, i=1; i<l; i++)
    for (j=0; j<l-1; j++)
      if (tren[j] > tren[j+1]){
        std::swap(tren[j], tren[j+1]);
        r++;
      }
  return r;
}

int main(){
  for (scanf("%d", &c); c--; printf("Optimal train swapping takes %d swaps.\n", bubblesort())){
    for (scanf("%d", &l), i = 0; i<l; scanf("%d", &tren[i++]));
  }
  return 0;
}
