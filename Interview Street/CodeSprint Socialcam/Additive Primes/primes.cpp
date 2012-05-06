// Andrés Mejía
using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <bitset>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

const int LIMIT = 10000000;

int sieve[LIMIT + 1]; // Inicializar con 0's.
int primes[LIMIT + 1];

void generate_primes() {
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
}

bool is_prime(int i) {
    if (i < 2) return false;
    return primes[sieve[i]] == i;
}

int main(){
    generate_primes();
    vector<int> additive;
    for (int i = 1; i <= LIMIT; ++i) {
        int p = primes[i];
        int sum = 0;
        while (p > 0) sum += p % 10, p /= 10;
        if (is_prime(sum)) additive.push_back(primes[i]);
    }
    int n;
    cin >> n;
    cout << additive[n - 1] << endl;
    
    return 0;
}