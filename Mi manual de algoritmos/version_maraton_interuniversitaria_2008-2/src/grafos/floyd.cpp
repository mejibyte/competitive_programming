#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

unsigned long long g[101][101];

int main(){
  int casos;
  cin >> casos;
  bool first = true;
  while (casos--){
    if (!first) cout << endl;
    first = false;

    int n, e, t;
    cin >> n >> e >> t;
    for (int i=0; i<n; ++i){
      for (int j=0; j<n; ++j){
	g[i][j] = INT_MAX;
      }
      g[i][i] = 0;
    }

    int m;
    cin >> m;
    while (m--){
      int i, j, k;
      cin >> i >> j >> k;
      g[i-1][j-1] = k;
    }

    for (int k=0; k<n; ++k){
      for (int i=0; i<n; ++i){
	for (int j=0; j<n; ++j){
	  g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
	}
      }
    }
    
    int r=0;
    e -= 1;
    for (int i=0; i<n; ++i){
      r += ((g[i][e] <= t) ? 1 : 0);      
    }

    cout << r << endl;
  }
  return 0;
}
