#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;

//Velocity = 20km/h = 20000mt/60min = 2000mt/6min
const double v = 2000.0 / 6.0; 

int main(){
  double x;
  int a, b, c, d, n;
  scanf("%d\n", &n);

  //cout << "n es: " << n << endl;

  while (n--){
    x = 0.0;
    scanf("%d %d\n", &a, &b);

    //cout << "a b son: " << a << " " << b << endl;
    
    string s;
    //getline(cin, s);
    //cout << "s es: " << s << endl;
    while (getline(cin, s) && sscanf(s.c_str(), "%d %d %d %d", &a, &b, &c, &d) == 4){
      //cout << "a b c d son: " << a << " " << b << " " << c << " " << d << endl;
      x += sqrt( (a-c)*(a-c) + (b-d)*(b-d) );
    }
    
    int t = floor((2 * x / v) + 0.5);
    
    printf("%d:%0.2d\n", t/60, t%60);
  }
  return 0;
}
