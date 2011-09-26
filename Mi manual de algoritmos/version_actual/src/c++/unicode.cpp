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
  wchar_t c;

  wstring s;
  while (getline(wcin, s)){
    wcout << L"Leí : " << s << endl;
    for (int i=0; i<s.size(); ++i){
      c = s[i];
      wprintf(L"%lc %lc\n", towlower(s[i]), towupper(s[i]));
    }
  }

  return 0;
}


