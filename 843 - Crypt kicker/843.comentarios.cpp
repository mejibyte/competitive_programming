#include <sstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>

using namespace std;

//Los diferentes diccionarios clasificados según la longitud de las cadenas que contienen:
map<int, set<string> > dict;
//Ej: dict[4] me da un set de strings que contiene todas las palabras dadas en el diccionario de longitud 4


//El mapeo ideal para una solución. Es decir, solucion['a'] == 'b' si cada 'a' que aparece en la línea la tengo que
//que reemplazar por una 'b' en la salida. 
map<char, char> solucion;
//La declaro como una variable global porque la necesito en varias funciones.


//Retorna verdadero si al intentar mapear todos los caracteres del parámetro <origen> a todos los caracteres de 
//<destino> se produce una contradicción o un mapeo ilegal.
//El último parámetro <crypt> contiene un mapeo de las palabras que se han visto hasta el momento de llamar
//esta función. Notar que el parámetro <crypt> se pasa por copia y no por referencia (Porque no tiene &).
//Esto lo hago porque <crypt> se modifica dentro de la función, y no me sirve que al llamar la función quede
//modificado afuera, entonces hago una copia que puedo modificar libremente sin riesgos.
bool contradice(const string &origen, const string &destino,  map<char, char> crypt){
  if (origen.length() != destino.length()) return true;

  for (int i=0; i<origen.size(); ++i){
    if (crypt.count(origen[i]) == 1){
      if (crypt[origen[i]] != destino[i]){ //Caso 1: Ya había asignado esta letra a otra diferente
	return true;
      }
    }else{
      for (map<char, char>::iterator j = crypt.begin(); j != crypt.end(); ++j){
	if ((*j).second == destino[i]) return true; //Caso 2: Ya existía otra letra diferente en <origen> a la que le
      }                                             //        habían asignado la misma letra
      crypt[origen[i]] = destino[i];
    }
  }
  return false;
}


//Realiza una asignación de todas las letras de <origen> a todas las de <destino>.
//Nuevamente notar que <crypt> es una copia.
map<char, char> asignar(const string &origen, const string &destino, map<char, char> crypt){
  if (origen.size() == destino.size()){
    for (int i=0; i<origen.size(); ++i){
      crypt[origen[i]] = destino[i];
    }
  }
  return crypt;
}

//Esta función es la más importante del programa, es la que se encarga de realizar la fuerza bruta.
//Los parámetros son:
//i -> la posición en el vector <words> que estamos intentando desencriptar
//words -> un vector con todas las palabras que queremos desencriptar
//crypt -> El mapeo de letras que hemos encontrado hasta ahora. Este parámetro se puede modificar 
//libremente dentro de la función porque es una copia.

//Retorna verdadero si logra desencriptar <words> o falso si no.
bool backtrack(const int &i, const vector<string> &words, map<char, char> crypt){
  //Si estoy intentado desencriptar una palabra FUERA del vector, es porque encontré una solución.
  if (i >= words.size()){
    solucion = crypt;
    return true;
  }
  
  int len = words[i].length();
  set<string> possible = dict[len];

  //Vamos a intentar todas las posibles opciones de desencriptación (?) de esta palabra.
  //Sabemos que tienen que ser de la misma longitud, así que en <possible> metemos el set de
  //palabras posibles de la misma longitud que aparecen en el diccionario
  for (set<string>::iterator j = possible.begin(); j != possible.end(); ++j){ //Para cada posible palabra...
    if (!contradice(words[i], (*j), crypt)){ //Si es una contradicción entonces sigue con la próxima palabra
      if (backtrack(i+1, words, asignar(words[i], (*j), crypt))){ //Sino, el éxito de la asignación
	                                                          //que hemos visto hasta ahora
	return true;                                              //depende del éxito que tengamos
	                                                          //al continuar la "rama del árbol"
      }
      
    }
    
  }
  return false; //Si llegamos hasta acá es porque ya evaluamos todas las posibles opciones y ninguna tuvo éxito.
}

int main(){
  int n;
  cin >> n;
  while (n--){
    string s;
    cin >> s;
    dict[s.length()].insert(s); //Clasifica las palabras según su longitud
  }
  getchar(); //Lee un dummy '\n'
  string line;
  while (getline(cin, line)){
   
    if (line == ""){
      cout << "\n";
      continue;
    }
    
    //Esta parte mete en <words> todas las palabras separadas. Utilizo un stringstream para hacer el split.
    vector<string> words;
    stringstream ss(line);
    string word;
    while (ss >> word){
      words.push_back(word);
    }
    
    //Si encuentro solución empezando en la primera palabra y empezando con un mapeo vacío...
    if (backtrack(0, words, map<char, char>() )){ 
      for (int i=0; i<line.size(); ++i){
	if (line[i] == ' ') cout << " ";
	else cout << solucion[line[i]]; //Imprimo la solución
      }
      cout << endl;
    }else{	
      for (int i=0; i<line.size(); ++i){
	if (line[i] == ' ') cout << " ";
	else cout << "*"; //Imprimo la no solución
      }
      cout << endl;
    }
  }
  return 0;
}
