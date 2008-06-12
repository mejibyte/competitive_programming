#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int temp;
    temp = 5 / 2;
    cout << temp << endl;
    if (temp == 2){
             cout << "C++ automaticamente usa division entera cuando la variable cuyo valor se asigna es de tipo entero.";
             cout << endl << endl;
    }
    system("PAUSE");
    return 0;
}
