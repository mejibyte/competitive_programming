/*
  Problem: 10167 - Birthday cake
  (From the UVa Online Judge)
  http://acm.uva.es/problemset/v101/10167.html

  Divide-and-conquer solution
  (Read problem "10077 - The Stern-Brocot number system" for an idea about the divide-and-conquer argument)
  Basically I binary-search the perfect slope to cut the cake. It really isn't BINARY search, but every
  time the space of slopes that can possibly be a solution is reduced considerably.

  Author: Andrés Mejía-Posada
  Date: May 6, 2008

  This code gets Accepted in the online judge.
  
 */
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

line operator |(const line &a, const line &b){
  line r;
  r.a = a.a + b.a;
  r.b = a.b + b.b;
  return r;
}

//Returns positive if p is to the left of line l
//Returns negative if p is to the right of line l
//Returns zero if p is colineal with line l
int cross(const point &p, const line &l){
  point q;
  q.x = l.b;
  q.y = -l.a;
  
  return (p.x*q.y - q.x*p.y);
}

//Returns positive if line l should rotate left
//Returns negative if line l should rotate right
//Returns zero if line l is a solution
int check(const vector<point> &c, const line &l){
  int left = 0, right = 0;
  for (int i=0; i<2*n; ++i){
    int t = cross(c[i], l);
    left  += (t>0);
    right += (t<0);
  }
  if (left == right && left < n){ //2 or more points are colineal with the cut
    return -1; //? Or return 1? Does it matter? (It also gets accepted with +1, 0 will give a wrong answer though).
  }
  return (left - right);
}


int main(){
  while (cin >> n && n){
    vector<point> cherry(2*n);
    for (int i=0; i<2*n; ++i){
      cin >> cherry[i].x >> cherry[i].y;
    }
    
    line uphigh, upmed, updown, downhigh, downmed, downdown;
    uphigh = line(1, 0);
    if (check(cherry, uphigh) == 0){
      cout << uphigh.a << " " << uphigh.b << endl;
      continue;
    }
    updown = line(0, 1);
    if (check(cherry, updown) == 0){
      cout << updown.a << " " << updown.b << endl;
      continue;
    }

    downhigh = line(0, 1);
    if (check(cherry, downhigh) == 0){
      cout << downhigh.a << " " << downhigh.b << endl;
      continue;
    }
    
    downdown = line(-1, 0);
    if (check(cherry, downdown) == 0){
      cout << downdown.a << " " << downdown.b << endl;
      continue;
    }
    
    while (true){


      upmed = uphigh | updown;
      int t = check(cherry, upmed);
      if (t == 0){
	cout << upmed.a << " " << upmed.b << endl;
	break;
      }else if (t < 0){
	uphigh = upmed;	
      }else{
	updown = upmed;
      }

      downmed = downhigh | downdown;
      t = check(cherry, downmed);
      if (t == 0){
	cout << downmed.a << " " << downmed.b << endl;
	break;
      }else if (t < 0){
	downhigh = downmed;	
      }else{
	downdown = downmed;
      }

    }
  }
  
  return 0;
}
