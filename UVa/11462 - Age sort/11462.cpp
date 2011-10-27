#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;


const int SIZE = 100;

int v[SIZE+1];

int main(){
  int n, i, j;
  while (scanf("%d", &n) == 1 && n){
    memset(v, 0, sizeof v);
    for (int i=0; i<n; ++i){
      scanf("%d", &j);
      ++v[j];
    }
    bool first = true;
    for (int i=1; i<=SIZE; ++i){
      while (v[i]--){
        if (!first) printf(" ");
        first = false;
        printf("%d", i);
      }
    }
    puts("");
  }
  return 0;
}
