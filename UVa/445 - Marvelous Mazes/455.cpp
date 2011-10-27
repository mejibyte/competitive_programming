#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>


using namespace std;

string multiplica(const string &c, const int &porCuanto){
       string temp="";
       for (int i=0; i<porCuanto; i++){
           temp += c;
       }
       return temp;
}

bool esNumero(const string &s){
     char c;
     for (int i=0; i<s.length(); i++){
         c = s.c_str()[i];
         if (c > 57 || c < 48){
               return false;
         }
     }
     return true;
}

int main(int argc, char *argv[])
{
    int cuantos=0;
    
    string entrada;
    while (cin.peek() != EOF){
        getline(cin, entrada);
        if (entrada == ""){
           cout << endl;
           cuantos=0;
           continue;
        }
        
        string subStr;
        for (int i=0; i<entrada.length(); i++){
            subStr = entrada.substr(i,1);
            if (esNumero(subStr)){
                cuantos += atoi(subStr.c_str());
            }
            else if (subStr == "!"){
                 cout << endl;
                 cuantos=0;
            }
            else if (subStr == "b"){
                 cout << multiplica(" ", cuantos);
                 cuantos=0;
            }
            else {
                 cout << multiplica(subStr, cuantos);
                 cuantos=0;
                 }
                        
        }
        cout << endl;
    }
    return 0;
}
 
