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
	px = (t*(t+1))/2;
	lx = a + u*t;
	++t;
      }
      --t;
      min = t;

      py = ly = 0;
      t = 1;
      while (py < ly){
	py = (t*(t+1))/2;
	ly = v*t;
	++t;
      }
      --t;
      
      if (t > min) min = t;
      cout << min << endl;
    }    
  }
  return 0;
}
