/* 
Problema: E Parking lot

Equipo No. 3

Sebastían Arcila - Andrés  Mejía
*/
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iterator>
#include <vector>
#include <sstream>

using namespace std;

struct carro{
       int id, donde;
       bool parked;
       carro(int ID, int Donde, bool Parked){
         id = ID;
         donde = Donde;
         parked = Parked;
       }
};

int main(){
  int casos;
  //fstream cin("parking.in");
  cin >> casos;
  //cout << "Lei casos: " << casos << endl;
  bool primerCaso = true;
  
  while (casos--){
    vector<carro> carros;   
    if (!primerCaso) cout << endl;
    primerCaso = false;
    int id;
    while (cin >> id && id != 99){
      //cout << "Lei id: " << id << endl;
      carros.push_back(carro(id, id, false));
    }
    
    /*cout << "Voy a imprimir carros:" << endl;
    for (int i=0; i<carros.size(); ++i){
        cout << carros[i].id << "-"<<carros[i].donde<<endl;
    }*/
    
    string line;
    getline(cin, line);
    while (getline(cin, line) && line != ""){
      stringstream ss(line);
      int salio;
      ss >> salio;
      //cout << "Lei salio: " << salio << endl;
      
      int posClosest = 9999;
      int minDistance = 9999;
      for (int i=0; i<carros.size(); ++i){
          int d;
          if (!carros[i].parked){
                                 
            if (carros[i].donde <= salio){
                d = salio - carros[i].donde;
            }else{
                d = (salio+20) - carros[i].donde;
            }
            if (d < minDistance){
                  minDistance = d;
                  posClosest = i;
            }
          }
      }
      //cout << "minDistance es " << minDistance << endl;
      //cout << "PosClosest es " << posClosest << endl;
      if (posClosest == 9999) continue;
      carros[posClosest].parked = true;
       carros[posClosest].donde = salio;
      
      for (int i=0; i<carros.size(); ++i){
        if (!carros[i].parked){
          int d = carros[i].donde + minDistance;
          while (d > 20) d -= 20;
          carros[i].donde = d;
        }
      }
      
      /*cout << "Voy a imprimir carros:" << endl;
      for (int i=0; i<carros.size(); ++i){
        cout << carros[i].id << "-"<<carros[i].donde<<endl;
      }*/
    }
    for (int i=0; i<carros.size(); ++i){
      cout << "Original position " << carros[i].id << " ";
      if (carros[i].parked){
        cout << "parked in " << carros[i].donde << endl;
      }else{
        cout << "did not park" << endl;
      }
    }
  }
  return 0;
}
