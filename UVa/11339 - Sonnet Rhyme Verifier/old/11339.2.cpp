#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

using namespace std;


int main() {
  wchar_t a[] = L"áéíóúñ";
  wchar_t b[] = L"ÁÉÍÓÚÑ";
  //assert(setlocale(LC_ALL, "en_US.UTF-8") != NULL);
  //assert(setlocale(LC_ALL, "") != NULL);

  for (int i=0; i<6; ++i){
    wprintf(L"el niño %lc in mayúsculas is %lc\n", a[i], towupper(a[i]));
    wcout << a[i] << " by wcout in caps is " << towupper(a[i]) << endl;
  }
  wcout << a << endl;
  wprintf(L"%ls\n", b);
  puts("vaya mierda");
  assert(sizeof(wchar_t) == 4);
  return 0;
}
