#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> point;
typedef pair<point, ll> disc;


inline ll distsqr(const point &a, const point &b){
  return (a.first - b.first)*(a.first - b.first) + (a.second - b.second)*(a.second - b.second);
}


int main(){
  int n;
  while (scanf("%d", &n) && (n > 0)){

    vector<disc> d(n);
    for (int i=0; i<n; ++i){
      ll x, y, r;
      cin >> x >> y >> r;
      d[i] = disc(point(x,y), r);
    }

    int k;
    bool ok = true;
    for (int i=1; i < n && ok; ++i){
      for (int j=0; j<i && ok; ++j){
	if (distsqr(d[i].first, d[j].first) >= (d[j].second * d[j].second)){
	  ok = false;
	  k = i;
	}
      }
    }
    
    cout << (ok?"F":"Unf") << "easible";
    if (!ok) cout << " " << k;
    cout << endl;
    
  }
  return 0;
}
