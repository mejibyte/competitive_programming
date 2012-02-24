//A -> (A)A | Epsilon

#include <iostream>
#include <string>

using namespace std;

bool ok;
char sgte;
int i;
string s;

bool match(char c){
  if (sgte != c){
    ok = false;
  }
  sgte = s[++i];
}

void A(){
  if (sgte == '('){
    match('(');
    A(); match(')'); A();
  }else if (sgte == '$' || sgte == ')'){
    //nada
  }else{
    ok = false;
  }
}

int main(){
  while(getline(cin, s) && s != ""){
    ok = true;
    s += '$';
    sgte = s[(i = 0)];
    A();
    if (i < s.length()-1) ok=false; //No consumí toda la cadena
    if (ok){
      cout << "Accepted\n";
    }else{
      cout << "Not accepted\n";
    }
  }
}
