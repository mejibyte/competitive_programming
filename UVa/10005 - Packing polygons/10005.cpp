#include <iostream>
#include <cmath>

using namespace std;

struct point{
  int x, y;
};

int main(){
  int n;
  while (cin >> n && n){
    point p[n];
    for (int i=0; i<n; ++i){
      cin >> p[i].x >> p[i].y;
    }
    double r;
    cin >> r;

    double longest = 0.0;
    for (int i=0; i<n; ++i){
      for (int j=i+1; j<n; ++j){
        longest = max(longest, hypot(p[i].x - p[j].x, p[i].y - p[j].y));
      }
    }
    if (longest < 2*r){
      cout << "The polygon can be packed in the circle." << endl;
    }else{
      cout << "There is no way of packing that polygon." << endl;
    }
  }
  return 0;
}
