#include <cstdlib>
#include <iostream>

using namespace std;

/*
The Cat in the Hat
Problema 107 de la ACM
por Andrés Mejía

http://acm.uva.es/p/v1/107.html

Fecha: 26/Febrero/2007

GT = Gatos trabajadores
GNT = Gatos no trabajadores
*/

bool isValidN(const int &N, const int &filas, const int &alturaGatoInicial){
     int tempAltura = alturaGatoInicial;
     for (int i=0; i < (filas-1); i++){
         if (tempAltura % (N + 1) != 0) return false; //si no es divisible retorna falso
         tempAltura /= (N + 1);
     }
     if (tempAltura == 1) 
         return true;
     else
         return false;         
}
     
int encontrarN(const int &numeroGatosTrabajadores, const int &alturaGatoInicial, int &SetFilas){
    //if (numeroGatosTrabajadores == 1) return 1;
    int posible = 1;
    int temp, filas;
    while (posible <= numeroGatosTrabajadores){
          temp = 1; filas = 1;
          while (temp < numeroGatosTrabajadores){
                temp = temp * posible;
                filas += 1;
          }
          
          //cout << "filas: " << filas << endl;
          
          if (temp == numeroGatosTrabajadores){
                   if (isValidN(posible, filas, alturaGatoInicial)){
                       SetFilas = filas;
                       return posible;
                       }
          }
          posible += 1;
    }
    return 0; //En teoria nunca debería pasar                        
}

int potenciar(const int &base, const int &exponente){
        int result = 1;
        for (int i=0; i<exponente; i++) {
            result = result * base;
        }
        return result;
}

int getGNT(const int &N, const int &filas){
    int result = 1;
    if (filas == 1) return 0;
    for (int i=1; i<(filas-1); i++){
        result += potenciar(N, i);
    }
    return result;
}

int getSumaAlturas(const int &N, const int &filas, int alturaPrimerGato){
    
    int suma = alturaPrimerGato;
    
    for (int i=1; i<filas; i++){
        alturaPrimerGato /= (N+1);
        suma += potenciar(N, i) * alturaPrimerGato;
    }
    return suma;
}
 
 
int main(int argc, char *argv[])
{   
    int alturaPrimerGato;
    int numeroGT;
    int filas;
    int N;
    
    while (cin >> alturaPrimerGato && cin >> numeroGT){
          if (alturaPrimerGato == 0 && numeroGT == 0) break;
          filas = 0;
          //cout << "N: " << encontrarN(numeroGT, alturaPrimerGato, filas) << endl;
          //cout << "filas: " << filas << endl;
          N = encontrarN(numeroGT, alturaPrimerGato, filas);
          cout << getGNT(N, filas) << " " << getSumaAlturas(N, filas, alturaPrimerGato) << endl; 
    }
    return 0;
}
