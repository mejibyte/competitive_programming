#include <iostream>
#include <math.h>
#include <cassert>

using namespace std;

main(){
  double a,b,c,s,r, temp;
  while (cin >> a >> b >> c){
    s = (a+b+c)/2;
    temp = s*(s-a)*(s-b)*(s-c);
    assert(temp >= 0);
    //cout << "s es : " << s << endl;
    if (s==0.0)
      r = 0.0;
    else
      r = sqrt(temp)/s;
    printf("The radius of the round table is: %0.3f\n", floor(r*1000+0.5)/1000);
  }
  return 0;
}
