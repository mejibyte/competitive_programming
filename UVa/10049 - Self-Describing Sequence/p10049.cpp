#include <cstdlib>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

vector<int> cambios;

int f(const int &n){
    int i=0;
    while (n >= cambios[i] && i < cambios.size()){
          i++;
    }
    //for (i=0; n >= cambios[i]; i++);
    //cout << "f("<< n << ") = " << i << endl;
    return i; 
}

void printCambios(){
     for (int i = 0; i<cambios.size(); i++){
         cout << cambios[i] << " ";
     }
     cout << endl;
}


void crearCambios(){
     cambios.push_back(1);
     cambios.push_back(2);
     cambios.push_back(4);
     cambios.push_back(6);
     cambios.push_back(9);
     //while(cambios[cambios.size()-1] < 20000000){
     while (cambios.size() < 700){
         int ultimo = cambios[cambios.size()-1];
         cambios.push_back(ultimo + f(f(ultimo)));
     }
     cout << "El tamaño de cambios es: " << cambios.size() << endl;
         
}
int main(int argc, char *argv[])
{
    //crearCambios();
    //printCambios();
    system("PAUSE");
    return EXIT_SUCCESS;
}
