#include<iostream>
#include<math.h>
using namespace std;

int cubo(int x){
  int i=1;
  while(i*i*i <= x){
    ++i;
  }
  --i;
  //    cout << i << endl;
  if (i*i*i == x){
    return i;
  }else{
    return INT_MAX;
  }
}

int main(){
  int n;
  while(cin>>n &&n){
    int y = 1;
    bool encontre=false;
    while (true){
      int r = cubo(n + (y*y*y));
      //      cout << "r es: " << r << " y es: " << y << endl;
      if (r != INT_MAX){
	cout << r << " " << y << endl;
	encontre = true;
	break;
      }
      ++y;
      if ((y+1)*(y+1)*(y+1) - y*y*y > n) break;
    }
    if (!encontre){
      cout << "No solution\n";
      continue;
    }
  }
}
