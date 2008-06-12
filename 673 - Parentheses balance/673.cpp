#include <string>
#include <iostream>

using namespace std;

bool valid(const string s){
  //cout << s << endl;
  if (s == "") return true;

  int p=0, b=0, i;
  for (i = 0; i<s.size(); ++i){
    if (s[i] == '(') ++p;
    if (s[i] == ')') --p;
    if (s[i] == '[') ++b;
    if (s[i] == ']') --b;

    if (p == 0 && b == 0){
      break;
    }

  }

  if (i < s.size()-1){
    return (valid(s.substr(0, i+1)) && valid(s.substr(i+1)));
  }

  char first = s[0];
  char last = s[s.size() - 1];
  if ( (first == '(' && last == ')') || (first == '[' && last == ']') ){
    return (valid(s.substr(1, s.size()-2)));
  }
  return false;
}

int main(){
  int n;
  cin >> n;
  while (getchar() != '\n');
  string s;
  while (n--){
    getline(cin, s);
    cout << (valid(s)?"Yes":"No") << endl;
  }
  return 0;
}
