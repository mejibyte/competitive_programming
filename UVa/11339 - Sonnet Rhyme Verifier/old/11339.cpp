/*
  C++ no sirve para trabajar con tildes. Que mierda!
 */

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>

using namespace std;

const string minu = "áéíóúñ";
const string mayu = "ÁÉÍÓÚÑ";
const string tildes = "áéíóúñÁÉÍÓÚÑ";
const string bad = " ¡!,.:;¿?-";

wchar_t toLower(wchar_t c){
  int t;
  if (bad.find(c) != string::npos) return c;
  if ((t = minu.find(c)) != string::npos){
    return c;
  }
  if ((t = mayu.find(c)) != string::npos){
    return minu[t];
  }
  return tolower(c);
}

bool isAlpha(wchar_t c){
  if (bad.find(c) != string::npos) return false;
  c = toLower(c);
  if (minu.find(c) != string::npos) return true;
  return isalpha(c);
}

void clean(string &s){
  cout << s << endl;

  int n = s.size();
  for (int i=0; i<n; ++i){
    s[i] = toLower(s[i]);
    if (bad.find(s[i]) != string::npos || (!isAlpha(s[i]) && tildes.find(s[i]) == string::npos)){
      s.erase(i, 1);
      --i;
      n = s.size();
    }
  }
  if (tolower(s[s.size()-1]) == 's'){
    s.erase(s.size()-1, 1);
  }
  cout << s << endl;
}

int main(){
  string sufijos, line;
  while (getline(cin, sufijos)){
    getline(cin, line);
    //Escribo el titulo
    cout << line << ": ";

    vector<string> p;
    while (getline(cin, line)){
      clean(line);
      if (line == "") break;
    }

    //Check here
  }
  return 0;
}
