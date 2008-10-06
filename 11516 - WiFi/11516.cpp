/*
  Problem: 11516 - WiFi
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

const int N = 100005;

int h[N], n;

bool solvable(double d, int r){
  int i = 0;
  //D(d), D(r);
  for (double pivot = h[0] + d; r--; pivot = h[i] + d){
    //D(pivot);
    while (i < n && h[i] <= pivot + d){
      ++i;
      //D(i);
    }
    if (i == n)
      return true;
  }
  return false;
}

int main(){
  int C;
  for (cin >> C; C--; ){
    int r;
    cin >> r >> n;
    for (int i=0; i<n; ++i)
      cin >> h[i];

    sort(h, h+n);
    int low = 0, high = h[n-1] - h[0];

    while (low < high){
      int mid = (low+high)/2;
      if (solvable(mid/2.0, r)){
	high = mid;
      }else{
	low = mid + 1;
      }
    }

    printf("%.1lf\n", low/2.0);
  }
  return 0;
}
