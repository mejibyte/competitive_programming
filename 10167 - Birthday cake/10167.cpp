#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;

struct point{
  int x, y;
  point() {}
  point(const int &X, const int &Y) : x(X), y(Y) {}
};

struct line{
  int a, b;
  line() {}
  line(const int &A, const int &B) : a(A), b(B) {}
};


//Returns positive if p is to the left of line l
//Returns negative if p is to the right of line l
//Returns zero if p is colineal with line l
int cross(const point &p, const line &l){
  point q;
  q.x = l.b;
  q.y = -l.a;
  
  return (p.x*q.y - q.x*p.y);
}

bool check(const vector<point> &c, const line &l){
  int left = 0, right = 0;
  for (int i=0; i<2*n; ++i){
    int t = cross(c[i], l);
    left  += (t>0);
    right += (t<0);
  }
  return (left == n && right == n);
}


int main(){
  while (cin >> n && n){
    vector<point> cherry(2*n);
    for (int i=0; i<2*n; ++i){
      cin >> cherry[i].x >> cherry[i].y;
    }
    
    bool found = false;
    for (int i=-500; i<=500 && !found; ++i){
      for (int j=-500; j<=500 && !found; ++j){
	if (check(cherry, line(i, j))){
	  cout << i << " " << j << endl;
	  found = true;
	}
      }
    }
    
  }
  
  return 0;
}
