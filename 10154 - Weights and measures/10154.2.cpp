#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

struct turtle{
  int w,s;
  turtle(int W, int S) : w(W), s(S) {}
  bool operator < (const turtle &y) const{
    return (s - w < y.s - y.w) ||
      (s - w == y.s - y.w && w < y.w) ||
      (s - w == y.s - y.w && w == y.w && y.s < y.w);
  }
  bool operator == (const turtle &y) const{return w == y.w && s == y.s;}
};
bool operator > (const turtle &x, const turtle &y){return !(x == y) && !(x < y);}

int main(){
  vector<turtle> t;
  int x, y;
  while (cin >> x >> y){
    assert(x <= y);
    t.push_back(turtle(x,y));
  }
  sort(t.begin(), t.end(), greater<turtle>() );

  /*for (int i=0; i<t.size(); ++i){
    cout << "turtle[i]: " << t[i].w << " " << t[i].s;
    cout << endl;
    }*/
  
  vector<int> p(t.size()), dp(t.size());
  for (int i=0; i<t.size(); ++i){
    dp[i] = 1;
    p[i] = t[i].s - t[i].w;
    for (int j=0; j<i; ++j){
      if (t[i].w <= p[j]){
	if (dp[i] < dp[j] + 1){
	  dp[i] = dp[j] + 1;
	  p[i] = min(p[j] - t[i].w, t[i].s - t[i].w);
	}
      }
    }
  }
  cout << *(max_element(dp.begin(), dp.end())) << endl;
  return 0;
}
