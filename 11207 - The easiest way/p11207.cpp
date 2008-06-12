#include <iostream>
#include <algorithm>

using namespace std;

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

int main(){
  unsigned int n;
  cin >> n;
  while (n){
    unsigned int vaGanando = 0;
    double ganador = 0.0;
    for (int i=1; i<=n; i++){ /* i nos dice en que pieza de papel vamos */
      unsigned long h, w;
      cin >> h >> w;
      if (w > h) swap(w, h);
      double maxPieza = MAX(MIN(h/4.0,w),MIN(h/2.0,w/2.0));
      if (maxPieza > ganador){
	ganador = maxPieza;
	vaGanando = i;
      }
    }
    cout << vaGanando << endl;
    cin >> n;
  }
  return 0;
}
