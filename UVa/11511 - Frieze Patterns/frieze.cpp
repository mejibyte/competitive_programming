#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;

int f[1005][1005];

int main(){
  int n, row, col;
  while (cin >> n >> row >> col && n){
    for (int i=0; i<n; ++i) cin >> f[i][0];
    for (int j=0; j<(n+1); ++j) f[0][j] = f[n-1][j] = 1;
    for (int j=1; j<(n+1); ++j)
      for (int i=1; i<n-1; ++i)
	f[i][j] = (f[i+1][j-1]*f[i-1][j]+1)/f[i][j-1];

    --row, --col;
    cout << f[row][col%(n+1)] << endl;
  }
  return 0;
}
