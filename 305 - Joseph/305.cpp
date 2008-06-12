#include <cstdlib>
#include <iostream>
#include <vector>

//#define DEBUG

using namespace std;

//retorna el minimo m para que se mueran todos los k malos antes que algún bueno
int minimoM(short k){
    vector<short> gente;
    gente.reserve(28);
    
    
    int posibleM = 2;
    
    while (true){
        //ensayar un posible m
        gente.clear();
        //Agregar el numero de personas
        for (short i=1; i<=2*k; i++)
            gente.push_back(i);
        int voyEn = (posibleM - 1) % gente.size();    
        while (gente.size() > k){ //Borrar aquí la gente que va muriendo
            gente.erase(gente.begin() + voyEn);
            voyEn = (voyEn + posibleM - 1) % gente.size();
        }
        #ifdef DEBUG
        for (int i=0; i < gente.size(); i++)
            cout << gente[i] << " ";
        cout << endl;
        #endif
        /*cout << "ensaye posible M " << posibleM << endl;
        cout << "y llegue a ";
        for (int i=0; i < gente.size(); i++)
            cout << gente[i] << " ";
        cout << endl;*/
        //char c; cin >> c;
        if (gente[0] == 1 && gente[k-1] == k){
            return posibleM;
        }else{
            posibleM++;
        }
    }
    
}

int main(int argc, char *argv[])
{
    //valores generados por fuerza bruta con la función de arriba
    //for (int i = 1; i < 14; i++) cout << i << " -> " << minimoM(i) << endl;
    int m[] = {0, 2, 7, 5, 30, 169, 441, 1872, 7632, 1740, 93313, 459901, 1358657, 2504881};
    int k;
    cin >> k;
    while (k > 0){
        cout << m[k] << endl;
        cin >> k;
    }
    return 0;
}
