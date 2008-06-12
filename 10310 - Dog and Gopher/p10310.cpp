#include <iostream>
#include <math.h>

using namespace std;

int main(){
  int n;
  double gx, gy, dx, dy;
  while (cin >> n >> gx >> gy >> dx >> dy){
    bool escaped = false;


    for (int i=0; i<n; ++i){
      
      double hx, hy;
      cin >> hx >> hy;
      if (!escaped){
	double d, g;
	g = sqrt(pow(gx - hx,2)+pow(gy - hy,2));
	d = sqrt(pow(dx - hx,2)+pow(dy - hy,2));
	if (g*2 <= d){
	  escaped = true;
	  printf("The gopher can escape through the hole at (%.3f,%.3f).\n", hx, hy);
	}
      }
    }
    if (!escaped) cout << "The gopher cannot escape.\n";

  }
  
  return 0;
}
