#include <stdio.h>
#include <math.h>
#include <iostream>

//#define DEBUGUEANDO

using namespace std;

int main()
{
    int n[32];
    int sizeN; //Numero de digitos de N
    unsigned int d; //equivalente decimal de n
    while (cin.peek() != EOF){
          //Leer linea
          sizeN = 0;
          while(cin.peek() != '\n'){
              n[sizeN] = cin.get() - 48;
               #ifdef DEBUGUEANDO
                cout <<  "Lei: " << n[sizeN] << " Size es: " << sizeN << endl;
               #endif
              sizeN++;
          }
          if (sizeN == 1 && n[0] == 0)
             break;
          #ifdef DEBUGUEANDO
          for (int i = 0; i < sizeN; i++)
              cout << n[i];
          cout << endl << "Size is: " << sizeN << endl;
          #endif
          //Procesar caso aquí
          d = 0;
          for (int i = 0; i<sizeN; i++){
              d += n[i] * ((int)pow(2, (sizeN - i)) - 1);
          }
          cout << d << endl;
          cin.get();              
    }
    return 0;
}
