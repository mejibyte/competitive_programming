#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

bool esPrimo(const int &n){
     if (n % 2 == 0)
        return false;
     else{
        int raiz = (int)ceil(sqrt(n)) + 1;
        for (int i=3; i<raiz; i += 2)
            if (n % i == 0)
                  return false;
        return true;
     }
}

int voltear(int n){
    int r=0;
    while (n > 0){
          r = r * 10 + n % 10;
          n /= 10;
    }
    return r;
}

int main()
{
    int n;
    while (cin >> n){
          if (!esPrimo(n))
             cout << n << " is not prime.\n";
          else{
                int inverso = voltear(n);
                if (inverso != n && esPrimo(inverso))
                   cout << n << " is emirp.\n";
                
                else
                   cout << n << " is prime.\n";  
          }
    }
    return 0;
}
