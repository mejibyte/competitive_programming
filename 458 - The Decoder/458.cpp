#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{   
    char c;
    while ((c = getchar()) != EOF){
          if (c != '\n'){
                 printf("%c", (c - 7));
          }
          else{
                 printf("\n");
          }
    }
    return 0;
}
