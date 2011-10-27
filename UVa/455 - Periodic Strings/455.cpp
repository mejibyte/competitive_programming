#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    int casos, posibleP;
    bool firstCase = true;
    cin >> casos;
    while (casos--){
          if (!firstCase) cout << endl;
          firstCase = false;          
          string ppal, semi, periodo;
          cin >> ppal;
          posibleP = 0;
          do{
                   posibleP++;
                   periodo = semi = ppal.substr(0, posibleP);
                   while (semi.length() < ppal.length()){
                         semi += periodo;
                   }
          } while (semi != ppal);
          cout << posibleP << endl;
    }
    return 0;
}
