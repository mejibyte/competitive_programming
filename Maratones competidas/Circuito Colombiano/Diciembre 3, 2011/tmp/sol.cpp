#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>
using namespace std;

int isPrime(long long X) {
  if (X<2) return 0;
  if (X==2) return 1;
  for (long long a=2; a*a<=X; a++) if (X % a == 0) return 0;
  return 1;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    int N,K;
    cin >> N >> K;
    vector<long long> V;
    for (int i=0; i<N; i++) {
      long long x;
      cin >> x;
      V.push_back(x);
    }

    int prime = 0;
    for (int i=0; i<N; i++) prime += isPrime(V[i]);

    if (prime > 0) {
      if (N > 1) { cout << "YES" << endl; continue; }
    }
    
    for (int i=0; i<N; i++) {
      long long x = V[i]-1;
      while (!isPrime(x)) x--;
      V[i] -= x;
    }
    
    int canWin = 0;
    for (int i=0; i<N; i++) canWin |= (V[i] <= K);
    if (canWin) { cout << "YES" << endl; continue; }
    
    for (int i=0; i<N; i++) V[i]-=K+1;

    long long grundy = 0;
    for (int i=0; i<N; i++) grundy ^= (V[i] % (K+1));

    cout << (grundy ? "YES" : "NO") << endl;
  }
}
