#include <iostream>
#include <algorithm>
using namespace std;

inline unsigned long b2d(string &s){
  reverse(s.begin(), s.end());
  unsigned long r = 0;
  unsigned long pow2 = 1;
  for (int i=0; i<s.size(); ++i){
    if (s[i] == '1')
      r += pow2;
    pow2 *= 2;
  }
  return r;
}

int gcd_short( int a, int b ) { return b ? gcd_short( b,  a % b ) : a; }

unsigned long gcd(unsigned long a, unsigned long b){
  unsigned long x = a, y = b, r;
  while (y != 0){
    r = x % y;
    x = y;
    y = r;
  }
  return x;
}

int main(){
  int n;
  cin >> n;
  for (int i=1; i<=n; ++i){
    string s,t;
    cin >> s >> t;
    unsigned long x = b2d(s), y = b2d(t);
    cout << "Pair #" << i << ": ";
    if (gcd(x,y) > 1)
      cout << "All you need is love!";
    else
      cout << "Love is not all you need!";
    cout << endl;
    
  }
  return 0;
}
