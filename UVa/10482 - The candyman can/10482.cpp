#include <iostream>

using namespace std;


void printBinary(const int& x){
  unsigned mask = 0x80000000;
  while (mask){
    cout << ((x & mask)?1:0);
    mask >>= 1;
  }
  cout << endl;
}

int main(){
  unsigned x;
  for (int i = 0; i<=32; ++i){
    x = 1 << i;
    printf("%u\n", x);
    //printf("%X\n", x);
    printBinary(x);
  }
  return 0;
}
