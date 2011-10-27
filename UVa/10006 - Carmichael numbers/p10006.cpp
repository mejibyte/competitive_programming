#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

const int MAX = 65001;

//p[x] == 0 si x es primo, sino p[x] == 1
int p[MAX];

//pot[i] contiene (a^(2^i))mod(n) 
long long pot[16];

//f retorna (a^n)mod(n). Solo funciona si a,n < 65000!
//corre en orden O(log_2(n))
long long f(long long a, long long n){
  string bin="";
  long long  r;
  long long temp = n;
  while (temp > 0){
    r = temp % 2;
    temp = temp / 2;
    bin = (char)('0'+r) + bin;
  }

  pot[0] = a % n;
  for (int i=1; i<16; ++i){
    pot[i] = (pot[i-1]*pot[i-1]) % n;
  }

  r=1;
  for (int i=0; i<bin.size(); ++i){
    if (bin[i] == '1'){
      r = (r * pot[bin.size()-i-1]) % n;
    }
  }
  return r;
}


bool c(int n){
  for (int a=2; a<n; ++a){
    //si no lo pasa return false
    long long r = f(a,n);
    if (r != a) return false;
  }
  return true;
}

int main(){

  for (int i=2; i<MAX; i++)
    if (!p[i])
      for (int j=2*i; j<MAX; j+=i)
        p[j] = 1;
  

  int n;
  while (scanf("%d", &n) == 1 && n > 0){
    if (!p[n] || !c(n)) printf("%d is normal.\n", n);
    else{
      printf("The number %d is a Carmichael number.\n", n);
    }
  }
  return 0;
}
