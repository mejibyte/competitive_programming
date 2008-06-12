#include <iostream>
#include <algorithm>
using namespace std;

int main(){
  string s = "int main(){ return 0; }";
  cout << s << endl;
  reverse(s.begin(), s.end());
  cout << s << endl;
  return 0;
}
