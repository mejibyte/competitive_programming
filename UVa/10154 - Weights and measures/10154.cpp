#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct turtle{
  int w,s;
  turtle(int W, int S) : w(W), s(S) {}
  bool operator < (const turtle &y) const{
    return (s - w < y.s - y.w) ||
      (s - w == y.s - y.w && w < y.w) ||
      (s - w == y.s - y.w && w == y.w && y.s < y.w);
  }
};

int main(){
  vector<turtle> t;
  int x, y;
  while (cin >> x >> y){
    t.push_back(turtle(x,y));
  }
  sort(t.begin(), t.end());

  /*for (int i=0; i<t.size(); ++i){
    cout << "turtle[i]: " << t[i].w << " " << t[i].s;
    cout << endl;
    }*/

  vector<int> p(t.size()), a(t.size());
  for (int i=0; i<t.size(); ++i){
    a[i] = 1;
    p[i] = t[i].w;
    for (int j=0; j<i; ++j){
      if (t[i].w + p[j] <= t[i].s && a[i] < a[j] + 1){
	a[i] = a[j] + 1;
	p[i] = p[j] + t[i].w;
      }
    }
  }
  cout << *(max_element(a.begin(), a.end())) << endl;
  return 0;
}
