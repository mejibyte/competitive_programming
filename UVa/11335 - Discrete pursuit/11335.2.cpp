#include <iostream>

using namespace std;

int main(){
  unsigned int a,u,v;
  while (cin >> a >> u >> v){
    if (a == 0){
      cout << "0" << endl;
    }else{
      unsigned int min, px, lx, py, ly, t;
      px = 0;
      lx = a;
      t = 0;
      while (px < lx){
	++t;
	px  += t;
	lx  += u;
      }
      min = t;

      py = 1;
      ly = v;
      t = 1;
      while (py < ly){
	++t;
	py += t;
	ly += v;
      }
      
      if (t > min) min = t;
      cout << min << endl;
    }    
  }
  return 0;
}
