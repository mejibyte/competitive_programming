#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    int casos;
    int n;
    int grades[1000];
    int superaron;
    double promedio, porcentaje;
    cin >> casos;
    while (casos--){
          //leer caso
          cin >> n;
          promedio = 0.0;
          for (int i=0; i<n; i++){
              cin >> grades[i];
              promedio += grades[i];
          }
          promedio /= n;
          //cout << "El promedio es: "<< promedio << endl;
          superaron = 0;
          for (int i=0; i<n; i++)
              if (grades[i] > promedio)
                 superaron++;
          //cout << superaron << " superaron el promedio." << endl;
          porcentaje = (double)superaron * 100 / n;
          porcentaje = floor(1000*porcentaje + 0.5)/1000; //round
          printf("%.3f", porcentaje); cout << "%\n";
          
    }
    return 0;
}
