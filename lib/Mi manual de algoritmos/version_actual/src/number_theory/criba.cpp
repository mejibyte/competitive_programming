// Complejidad: O(n)

const int LIMIT = 31622779;

int sieve[LIMIT + 1]; // Inicializar con 0's.
int primes[LIMIT + 1];

int primeCount = 1;
for (int i = 2; i <= LIMIT; ++i) {
  if (!sieve[i]) {
    primes[primeCount] = i;
    sieve[i] = primeCount;
    primeCount++;
  }

  for (int j = 1; j <= sieve[i] && i * primes[j] <= LIMIT; j++){
    sieve[ i * primes[j] ] = j;
  }
}

// primes contiene la lista de primos <= LIMIT, en los índices
// 1 a primeCount.
// ¡El primer primo está en la posición 1 y no 0!

// sieve[i] contiene el índice en el arreglo primes del primo
// más pequeño  que divide a i. Con esta información se puede
// saber si un número es primo o descomponerlo en primos si es
// compuesto.

// i es primo si primes[sieve[i]] == i, y compuesto si no.