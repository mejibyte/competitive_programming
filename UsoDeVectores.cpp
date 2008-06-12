#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool compara(int i, int j){
    return i < j;
}

main(){
  //Inicializa el vector v con 15 veces un 1
  vector<int> v(15, 1);
  
  //Copia el contenido de v a v2
  vector<int> v2(v);
  
  //Borra v2 y le asigna 10 4's
  v2.assign(10, 4);

  v2.clear();
  for (int i=1; i<=10; i++)
      v2.push_back(11-i);

  //Borra desde el tercer elemento (incluido) hasta tres elementos antes del final
  //Ej. de 1 2 3 4 5 6 7 8 9 10
  //queda 1 2 8 9 10
  v2.erase(v2.begin()+2, v2.end()-3);

  //muestra el ultimo elemento
  cout << *v2.begin() << " " << v2.front() << endl; 

  //muestra el ultimo elemento
  cout << *(v2.end()-1) << " " << v2.back() << endl;  
  
  //muestra mayor cantidad de elementos que este vector puede almacenar
  cout << v2.max_size() << endl;
  
  //ordena todo el vector de menor a mayor
  sort(v2.begin(), v2.end());
  sort(v2.begin(), v2.end(), compara);
  
  for (vector<int>::iterator it=v2.begin(); it<v2.end(); it++){
      cout << *it << " ";
  }
  cout << "\n";
  return 0;
}
