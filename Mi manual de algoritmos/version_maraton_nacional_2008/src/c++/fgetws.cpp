#include <iostream>
#include <cassert>
#include <stdio.h>
#include <assert.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>


using namespace std;

int main(){
  assert(setlocale(LC_ALL, "en_US.UTF-8") != NULL);
  wchar_t in_buf[512], out_buf[512];
  swprintf(out_buf, 512, L"¿Podrías escribir un número?, Por ejemplo %d. ¡Gracias, pingüino español!\n", 3);
  fputws(out_buf, stdout);

  fgetws(in_buf, 512, stdin);
  int n;
  swscanf(in_buf, L"%d", &n);

  swprintf(out_buf, 512, L"Escribiste %d, yo escribo ¿ÔÏàÚÑ~\n", n);
  fputws(out_buf, stdout);

  return 0;
}


