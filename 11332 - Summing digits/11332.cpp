#include <iostream>
using namespace std;

int main(){
 unsigned int n;
 while (cin >> n && n)
   cout << (n%9>0 ? n%9 : 9) << endl;
 return 0;
}
