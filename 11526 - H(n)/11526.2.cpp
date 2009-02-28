#include <iostream>
#include <cstdio>
using namespace std;

int n;
int main(){
  int t; scanf("%d", &t);
  while (t-- && scanf("%d", &n)==1){
    if (n <= 0){ puts("0"); continue; }

    long long res = 0;
    unsigned int i = 1;
    while (i <= n){
      int k = n / i;
      int j = n / k;
      if (k <= 0 || j <= 0 || i <= 0) for(;;);
      res += 1LL * (j - i + 1) * k;
      i = j + 1;
    }
    printf("%lld\n", res);
  }
  return 0;
}
