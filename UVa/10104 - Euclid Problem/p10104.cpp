#include <iostream>
#include <math.h>
using namespace std;

long long gcd(long long p, long long q, long long *x, long long *y){
  long long x1, y1;
  long long g;
  
  if (q>p) return(gcd(q,p,y,x));
  if (q == 0){
    *x = 1;
    *y = 0;
    return p;
  }
  g = gcd(q, p%q, &x1, &y1);
  *x = y1;
  *y = (x1 - floor(p/q)*y1);
  return g;
}

int main(){
  long long a, b, x, y, d, k;
  while (cin >> a >> b){
    
    d = gcd(a,b,&x,&y);
    cout << x << " " << y << " " << d << endl;
    //cout << d << endl;
    //bool found = false;
    //for (y=1; !found; ++y){
      /*x = 0;
      do{
	k = a*x + b*y;
	--x;
	}while(k > d);

      if (k == d){
	found = true;
	++x;
	--y;
	}*/
      //double c = 1.0*(d - b*y)/a;
      //cout << "c es: " << c << endl;
      //if (c == floor(c)){ //es entero
    //found = true;
    //x = (long long)c;
    //--y;
    //}
    //}
    
    //cout << x << " " << y << " " << d << endl;
    //printf("%lld %lld %lld\n", x, y, d);


  }
  return 0;
}
