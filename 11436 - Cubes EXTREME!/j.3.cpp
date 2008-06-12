#include<iostream>
#include<math.h>
#include <set>

using namespace std;

typedef unsigned long long ull;

inline ull cube(ull x){ return x*x*x; }

int main(){
  ull n;
  while(cin>>n &&n){
    bool found = false;
    for (ull k = 1; k*k<=n && k <= 29241; ++k){
      if (n % k != 0 ||
	  3*k*k*k*k > 12*k*n){
	continue;
      }
      ull y = ( -3*k*k + (ull)sqrt(12*k*n - 3*k*k*k*k) ) / (6*k);
      if (y > 0 && cube(y+k) - cube(y) == n){
	//	cout << "k: " << k << endl;
	cout << y + k << " " << y << endl;
	found = true;
	break;
      }
      /*if (k*k < n){
	k = n/k;
	ull y = ( -3*k*k + (ull)sqrt(12*k*n - 3*k*k*k*k) ) / (6*k);
	if (y > 0 && cube(y+k) - cube(y) == n){
	  //	cout << "k: " << k << endl;
	  cout << y + k << " " << y << endl;
	  found = true;
	  break;
	}
	k = n/k;
	}*/
    }

    if (!found){
      cout << "No solution" << endl;
    }
  }
  return 0;
}
