#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <sstream>
using namespace std;

typedef set<string> words;

int main(){
  words w;
  string s;
  while (getline(cin, s)){
    for (int i=0; i<s.size(); ++i){
      s[i] = tolower(s[i]);
      if (!isalpha(s[i])) s[i] = ' ';
    }
    stringstream ss(s);
    while (ss >> s){
      w.insert(s);
    }
  }
  for (words::iterator i = w.begin(); i != w.end(); ++i){
    cout << (*i) << endl;
  }
  return 0;
}
