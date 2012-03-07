
/*
  Problem: 2912. Super Primes (SPOJ)
  Author: Andrés Mejía-Posada
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>
using namespace std;


const int LIMIT = 10000000;

int sieve[LIMIT + 1]; // Inicializar con 0's.
int primes[LIMIT + 1];

// Returns the number of primes that were generated.
int buildSieve() {
  int primeCount = 1;
  for (int i = 2; i <= LIMIT; ++i) {
    if (!sieve[i]) {
      primes[primeCount] = i;
      sieve[i] = primeCount;
      primeCount++;
    }

    for (int j = 1; j <= sieve[i] and i * primes[j] <= LIMIT; j++){
      sieve[ i * primes[j] ] = j;
    }
  }
  return primeCount;
}


int main(){
  int primeCount = buildSieve();

  for (int i = 1; i <= primeCount && primes[i] <= primeCount; ++i){
    printf("%d\n", primes[ primes[i] ]);
  }
  return 0;
}

