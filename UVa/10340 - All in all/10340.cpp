#include <iostream>
#include <string>

using namespace std;

int main(){
  string s, t;
  while (cin >> s >> t){
    int i, j;
    for (i=0, j=0; i<s.size() && j<t.size(); ++j){
      i += (s[i] == t[j]);
    }
    cout << (i == s.size() ? "Yes":"No") << endl;
  }
}
