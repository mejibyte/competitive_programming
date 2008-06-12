#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int casos;
    scanf("%d", &casos);
    while (casos--){
        int x1, x2, temp, temp2;
        scanf("%x",&x2); //<---- read number in hexdecimal system(i.e. 265) 
        //en x2 queda en hexadecimal, ahora convertirlo a decimal.
        temp2 = x1 = 0;
        temp = x2;
        while (temp > 0){ //Convierto a decimal pero con la cifra menos significativa a la izquierda
              temp2 = temp2 * 10 + temp % 16;
              temp /= 16;
        }
        while (temp2 > 0){ //Invierto para que quede con cifra menos significativa a la derecha
              x1 = x1 * 10 + temp2 % 10;
              temp2 /= 10;
        }
        //Aqui en x1 y en x2 esta procesado correctamente el num en decimal.
        int b = 0;
        temp2 = 0;
        temp = x1;
        while (temp > 0){
              temp2 = temp2 * 10 + temp % 2;
              temp /= 2;
        }
        while (temp2 > 0){ //Invierto para que quede con cifra menos significativa a la derecha
              b = b * 10 + temp2 % 10;
              temp2 /= 10;
        }
        int b1 = 0;
        while (b){
              if (b % 10 == 1)
                 b1++;
              b /= 10;
        }
        printf("%d ", b1);
        b = 0;
        temp2 = 0;
        temp = x2;
        while (temp > 0){
              temp2 = temp2 * 10 + temp % 2;
              temp /= 2;
        }
        while (temp2 > 0){ //Invierto para que quede con cifra menos significativa a la derecha
              b = b * 10 + temp2 % 10;
              temp2 /= 10;
        }
        b1 = 0;
        while (b){
              if (b % 10 == 1)
                 b1++;
              b /= 10;
        }
        printf("%d\n", b1);
    }
    return 0;
}
