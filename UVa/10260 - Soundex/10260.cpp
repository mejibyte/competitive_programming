#include <iostream>
#include <map>
#include <sstream>

using namespace std;

map<string, char> d;

int main(int argc, char const *argv){
  d["AEIOUHWY"] = '0';
  d["BFPV"] = '1';
  d["CGJKQSXZ"] = '2';
  d["DT"] = '3';
  d["L"] = '4';
  d["MN"] = '5';
  d["R"] = '6';
  string s;
  while (getline(cin, s)){
    string r = "";
    int j = 0;
    for (int j = 0; j < s.size(); ++j){
      for (map<string, char>::iterator i = d.begin(); i != d.end(); ++i){
        if (i->first.find(s[j]) != string::npos){
          r += i->second;
          break;
        }
      }
    }
    for (int i=0; i<r.size()-1; ++i){
      if (r[i] == r[i+1]){
        r.erase(i, 1);
        --i;
      }
    }
    for (int i=0; i<r.size(); ++i){
      if (r[i] != '0'){
        cout << r[i];
      }
    }
    cout << endl;
  }
  return 0;
}
