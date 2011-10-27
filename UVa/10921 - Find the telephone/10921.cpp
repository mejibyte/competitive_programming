#include <iostream>
#include <string>

using namespace std;

string l[] = {"0", "1", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV", "WXYZ"};

int translate(char c){
  for (int i=0; i<10; ++i){
    if (l[i].find(c) != string::npos){
      return i;
    }
  }
  return -1;
}

int main(){
  string s;
  while (getline(cin, s)){
    for (int i=0; i<s.size(); ++i){
      if (s[i] == '-') cout << "-";
      else cout << translate(s[i]);
    }
    cout << endl;
  }
  return 0;
}
