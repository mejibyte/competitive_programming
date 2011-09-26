#include <iostream>
#include <fstream>
using namespace std;
int _main(){ freopen("entrada.in", "r", stdin);
  freopen("entrada.out", "w", stdout); string s; while (cin >>
  s){ cout << "Leí " << s << endl; } return 0; } int main(){
  ifstream fin("entrada.in"); ofstream fout("entrada.out");
  string s; while (fin >> s){ fout << "Leí " << s << endl; }
  return 0; }
