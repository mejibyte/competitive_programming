/*
  Problem: A - Cranes
  Author: Andrés Mejía-Posada
  (http://blogaritmo.factorcomun.org)

 */

using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>

#define D(x) cout << #x " is " << x << endl

double pi = acos(-1.0);

struct crane{
  int x, y, r;
};

inline double distsqr(int x1, int y1,    int x2, int y2){ return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);}

bool colapse(crane &a, crane &b){
  return (distsqr(a.x,a.y,  b.x,b.y)  <= (a.r + b.r)*(a.r + b.r) );
}

int main(){
  int C;
  for(cin >> C; C--;){
    int n;
    cin >> n;

    vector<crane> v(n);
    for (int i=0; i<n; ++i) cin >> v[i].x >> v[i].y >> v[i].r;

    vector<pair<int, int> > bad;
    for (int i=0; i<n; ++i)
      for (int j=i+1; j<n; ++j)
	if (colapse(v[i], v[j])){
	    bad.push_back(make_pair(i, j));
	    //cout << "choque " << i << " " << j << endl;
	}

    int ans = 0;

    for (int mask=1; mask < (1<<n); ++mask){
      bool ok = true;
      for (int i=0; i<bad.size(); ++i){
	int &x = bad[i].first, &y = bad[i].second;
	if ( (mask & (1 << x)) && (mask & (1 << y)) ){
	    ok = false;
	    break;
	}
      }

	if (!ok) continue;

	int sum = 0;
	for (int i=0; i<n; ++i){
	  if (mask & (1 << i)){
	    sum += v[i].r*v[i].r;
	  }
	}
	ans = max(ans, sum);
    }
    cout << ans << endl;
	    

  }
  return 0;
}
