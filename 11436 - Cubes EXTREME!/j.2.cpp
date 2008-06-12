#include<iostream>
#include<math.h>
#include <set>

using namespace std;

typedef unsigned long long ull;

set<ull> cubos;



int main(){
  ull n;
  for (ull i = 1; i < 2642246; ++i){
    cubos.insert(cubos.end(), i*i*i);
  }
  /*set<ull>::iterator i = cubos.end();
  --i;
  cout << (*i) << endl;*/

  while(cin>>n &&n){
    set<ull>::iterator i = cubos.upper_bound(n);
    cout << "(*i) es: " << (*i) << endl;
    if (i != cubos.end()){
      set<ull>::iterator j = cubos.find((*i) - n);
      if (j != cubos.end()){
	cout << "(*j) es: " << (*j) << endl;
	cout << (ull)pow((*i), 1./3.) << " " << (ull)pow((*j), 1./3.) << endl;
      }else{
	cout << "No solution\n";
      }
    }else{
      cout<< "No solution\n";	  
    }
  }
}
