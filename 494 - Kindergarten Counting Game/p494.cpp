#include <iostream>
#include <sstream>
#include <string>

using namespace std;


bool isVocal(const string &s){
 string vocs = "aAeEiIoOuU";
 for (int i=0; i<vocs.length(); i++){
   if (s == vocs.substr(i, 1)){
     return true;
   }
 }
 return false;
}

bool isAlpha(const string &s){
    for (int i=0; i<s.length(); i++){
        if (!isalpha(s.at(i))){
            return false;
        }
    }
    return true;
}

string procesar(const string &s){
      if (isVocal(s.substr(0,1))){
             return (s + "ay");
     }else{
         return (s.substr(1, s.length()-1) + s.substr(0,1)+"ay");
     }
}


int main(){

 string entrada, temp;
 int cuenta;
 while ( getline(cin, entrada) ){
    entrada += "\n";
    temp = "";
    cuenta = 0;
    int len = entrada.length();
    for (int i=0; i<len; i++){
        if (!isAlpha(entrada.substr(i,1))){
            if (temp.length() > 0){
                //cout << procesar(temp);
                cuenta++;
            }
            temp = "";
            //cout << entrada[i];
        }else{
            temp += entrada[i];
        }
    }
    cout << cuenta << endl;

 }

}
