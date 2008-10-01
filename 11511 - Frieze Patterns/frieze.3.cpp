/*
  Accepted
 */
#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;

int f[1005][1005];

int main(){
  int n, row, col;
  while (cin >> n >> row >> col && n){

    for (int i=1; i<=n; ++i) cin >> f[i][1];

    for (int j=1; j<=n+1; ++j) f[1][j] = f[n][j] = 1;

    for (int j=2; j<=n+1; ++j)
      for (int i=2; i<n; ++i)
	f[i][j] = (f[i+1][j-1]*f[i-1][j]+1)/f[i][j-1];


    /*
    for (int i=1; i<=n; ++i){
      for (int j=1; j<=n+1; ++j)
	printf("%3d ", f[i][j]);
      puts("");
    }
    */
    if (col % (n+1) == 0) col = n+1;
    else col %= (n+1);

    cout << f[row][col] << endl;
  }
  return 0;
}
