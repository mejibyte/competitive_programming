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
      crypt[origen[i]] = destino[i];
    }
  }
  return false;
}

map<char, char> asignar(const string &origen, const string &destino, map<char, char> crypt){
  if (origen.size() == destino.size()){
    for (int i=0; i<origen.size(); ++i){
      crypt[origen[i]] = destino[i];
    }
  }
  return crypt;
}

bool bt(const int &i, const vector<string> &words, map<char, char> crypt){
  if (i >= words.size()){
    solucion = crypt;
    return true;
  }
  
  int len = words[i].length();
  set<string> possible = dict[len];
  
  for (set<string>::iterator j = possible.begin(); j != possible.end(); ++j){
    if (!contradice(words[i], (*j), crypt)){
      if (bt(i+1, words, asignar(words[i], (*j), crypt))){
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
  }
  getchar();
  string line;
  while (getline(cin, line)){
   
    if (line == ""){
      cout << "\n";
      continue;
    }
    
    vector<string> words;
    stringstream ss(line);
    string word;
    while (ss >> word){
      words.push_back(word);
    }
    
    if (bt(0, words, map<char, char>() )){
      for (int i=0; i<line.size(); ++i){
	if (line[i] == ' ') cout << " ";
	else cout << solucion[line[i]];
      }
      cout << endl;
    }else{	
      for (int i=0; i<line.size(); ++i){
	if (line[i] == ' ') cout << " ";
	else cout << "*";
      }
      cout << endl;
    }
  }
  return 0;
}
