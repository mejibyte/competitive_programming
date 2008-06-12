#include <iostream>
#include <map>
#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

typedef pair<int,int> point;

vector<int> p;
int cache[1001][1001];

int f(point n){
  int i = n.first, j = n.second;
  //  cout << "n: " << n.first << " " << n.second << endl;
  if (cache[i][j] != -1){
    //cout << "Retornando " << cache[n] << endl;
    return cache[i][j];
  }
  //first < second
  if (n.second < n.first) swap(n.first, n.second);
  
  for (int k=0; k<p.size()-1; ++k){
    if (p[k]<=n.first && n.first<=p[k+1] &&
	p[k]<=n.second && n.second<=p[k+1]){
      //cout << "Retornando 0" << endl;
      return cache[i][j] = 0;
    }
  }

  int min=INT_MAX;
  for (int k=0; k<p.size(); ++k){
    if (n.first<p[k] && p[k]<n.second){
      int q = n.second - n.first + f(point(n.first, p[k])) + f(point(p[k], n.second));      
      //cout << "q es: " << q << endl;
      if (q < min){
	min = q;
      }
    }
  }
  //cout << "min es: " << min << endl;
  //cout << "Retornando " << min << endl;
  return   cache[i][j] = min;
  
}

int main(){
  int l;
  while (cin >> l && l > 0){
    int n;
    cin >> n;
    memset(cache, -1, sizeof(cache));
    p = vector<int>(n+2);
    p[0] = 0;
    p[n+1] = l;
    for (int i=1; i<=n; ++i){
      cin >> p[i];
    }
    cout << "The minimum cutting is " << f(point(0, l)) << ".\n";
  }
  return 0;
}
