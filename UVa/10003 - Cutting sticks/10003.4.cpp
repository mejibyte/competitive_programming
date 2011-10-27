#include <iostream>
#include <map>
#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

vector<int> p;
int cache[1001][1001];

int f(int i, int j){
  if (cache[i][j] != -1){
    return cache[i][j];
  }
  if (j < i) swap(i, j);
  
  for (int k=0; k<p.size()-1; ++k){
    if (p[k] <= i && i <= p[k+1] &&
	p[k] <= j && j <= p[k+1]){
      return cache[i][j] = 0;
    }
  }

  int min = INT_MAX;
  for (int k=0; k<p.size(); ++k){
    if (i < p[k] && p[k] < j){
      int q = j - i + f(i, p[k]) + f(p[k], j);      
      if (q < min){
	min = q;
      }
    }
  }
  return   cache[i][j] = min;
  
}

int main(){
  int l;
  while (cin >> l && l > 0){
    int n;
    cin >> n;
    p = vector<int>(n+2);
    p[0] = 0;
    p[n+1] = l;
    for (int i=1; i<=n; ++i){
      cin >> p[i];
    }
    for (int i=0;i<=n+1;++i){
      for (int j=i;j<=n+1;++j){
	cache[p[i]][p[j]]=-1;
      }
    }
    cout << "The minimum cutting is " << f(0, l) << ".\n";
  }
  return 0;
}
