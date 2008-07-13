#include <iostream>
#include <map>
#include <cassert>
#include <algorithm>
#include <cmath>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

map<ull, long long> cache;

void f(ull x)
{
  ull i;                 /* counter */
  ull c;                 /* remaining product to factor */
  ll r = cache[x];
  if (r == 0){
    c = x;
    while ((c % 2) == 0) {
      //printf("2\n");
      c = c / 2;
      r = 2;
    }
    i = 3;
    ull raiz = sqrt(c)+1;
    while (i <= raiz) {
      if ((c % i) == 0) {
        //printf("i: %lld\n", i);
        c = c / i;
        raiz = (sqrt(c)+1);
        r = i;
      }
      else
        i = i + 2;
    }
    if (c > r){
      r =  c;
      //printf("c: %lld\n", c);
    }
    //printf("c quedo en: %lld\n", c);
    //printf("r quedo en: %lld\n", r);

    c = r;
    while (c <= x){
      if (c == x){
        r = -1;
        break;
      }
      c *= r;
    }
    cache[x] = r;
  }
  printf("%lld\n", r);
  //assert(r < x);
}


int main(){
  long long n;
  while (scanf("%lld", &n) == 1 && n){
    if (n < 0) n *= -1;
    //assert(n > 0);
    f(n);
  }
  return 0;
}
