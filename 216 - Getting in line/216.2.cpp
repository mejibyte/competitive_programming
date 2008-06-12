/*
  Accepted
 */
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define popcount(x) __builtin_popcount(x)

using namespace std;

struct state{
  int i, v;
  double w;
  vector<int> o;
  state(int I, int V, double W, vector<int> O) : i(I), v(V), w(W), o(O) {}
  bool operator < (const state &that) const {
    return w > that.w;
  }
};


int main(){
  int n, N=1;
  while (cin >> n && n){
    
    vector<pair<int, int> > p(n);
    for (int i=0; i<n; ++i){
      cin >> p[i].first >> p[i].second;
    }

    double g[n][n];
    for (int i=0; i<n; ++i){
      for (int j=0; j<n; ++j){
	g[i][j] = hypot(p[i].first - p[j].first, p[i].second - p[j].second) + 16.0;
      }
    }

    double d[1<<n][n];
    for (int i=0; i<(1<<n); ++i){
      for (int j=0; j<n; ++j){
	d[i][j] = 1E100;
      }
    }

    priority_queue<state> q;
    for (int i=0; i<n; ++i){
      d[1<<i][i] = 0;
      q.push(state(i, 1<<i, 0.0, vector<int>(1, i)));
    }

    while (q.size()){
      state top = q.top();
      q.pop();

      //printf("Saqué de la pila: i = %d, v = %x, w = %lf\n", top.i, top.v, top.w);

      if (d[top.v][top.i] < top.w) continue;

      if (popcount(top.v) == n){ //Solution
	printf("**********************************************************\n");
	printf("Network #%d\n", N++);
	double t = 0.0;
	for (int i=0; i<n-1; ++i){
	  printf("Cable requirement to connect (%d,%d) to (%d,%d) is %.2f feet.\n",
	 	 p[top.o[i]].first, p[top.o[i]].second,
		 p[top.o[i+1]].first, p[top.o[i+1]].second,
		 g[top.o[i]][top.o[i+1]]);
	  t += g[top.o[i]][top.o[i+1]];
	}
	printf("Number of feet of cable required is %.2f.\n", t);
	break;
      }

      for (int i=0; i<n; ++i){
	//printf("Intetando ir al vecino %d\n", i);
	if ((top.v & (1<<i)) == 0){ //Si no había visitado el i
	  if (top.w + g[top.i][i] < d[top.v | (1<<i)][i]){
	    d[top.v | (1<<i)][i] = top.w + g[top.i][i];
	    top.o.push_back(i);
	    q.push(state(i, top.v | (1<<i), top.w + g[top.i][i], top.o));
	    top.o.erase(top.o.end() - 1);
	  }
	}
      }
    }
  }
  return 0;
}
