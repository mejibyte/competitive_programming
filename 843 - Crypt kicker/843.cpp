#include <sstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>

using namespace std;

map<int, set<string> > dict;
map<char, char> solucion;


bool contradice(const string &origen, const string &destino,  map<char, char> crypt){
  //cout << "Contradice llamado con " << origen << " y " << destino << endl;

  map<char, char> temp;
  for (int i=0; i<origen.size(); ++i){
    if (temp.count(origen[i]) == 1){
      if (temp[origen[i]] != destino[i]){
	return true;
      }
    }else{
      for (map<char, char>::iterator j = temp.begin(); j != temp.end(); ++j){
	if ((*j).second == destino[i]) return true;
      }
      temp[origen[i]] = destino[i];
    }
  }

  if (origen.length() != destino.length()) return true;

  for (int i=0; i<origen.size(); ++i){
    if (crypt.count(origen[i]) == 1){
      if (crypt[origen[i]] != destino[i]){
	return true;
      }
    }else{
      for (map<char, char>::iterator j = crypt.begin(); j != crypt.end(); ++j){
	if ((*j).second == destino[i]) return true;
      }
    }
  }
  return false;
}



void asignar(const string &origen, const string &destino, map<char, char> &crypt){
  if (origen.size() != destino.size()) return;

  for (int i=0; i<origen.size(); ++i){
    crypt[origen[i]] = destino[i];
  }
}

bool bt(int i, const vector<string> &words, map<char, char> crypt){
  if (i >= words.size()){
    solucion = crypt;
    return true;
  }
  
  int len = words[i].length();
  set<string> possible = dict[len];
  
  for (set<string>::iterator j = possible.begin(); j != possible.end(); ++j){

    if (!contradice(words[i], (*j), crypt)){
      map<char, char> copia = crypt;
      asignar(words[i], (*j), copia);
      
      if (bt(i+1, words, copia)){
	return true;
      }
      
    }
  }
  return false;
}

int main(){
  int n;
  cin >> n;
  while (n--){
    string s;
    cin >> s;
    dict[s.length()].insert(s);
    //cout << "agregue " << s << " al dict en la posicion " << s.length() << endl;
  }
  getchar();
  string line;
  while (getline(cin, line)){
    //cout << "Lei esta linea: " << line << endl;

    if (line == ""){
      cout << "\n";
      continue;
    }
    
    vector<string> words;
    stringstream ss;
    ss << line;
    string word;
    while (ss >> word){
      words.push_back(word);

      //cout << "Empuje la palabra " << word << " a la lista " << endl;

    }
    if (bt(0, words, map<char, char>() )){
      for (int i=0; i<line.size(); ++i){
	if (line[i] == ' ') cout << " ";
	else cout << solucion[line[i]];
      }
      cout << endl;
      //cout << "Hay solucion\n";
    }else{	
      for (int i=0; i<line.size(); ++i){
	if (line[i] == ' ') cout << " ";
	else cout << "*";
      }
      cout << endl;
      //cout << "No hay solucion\n";
    }
  }
}
