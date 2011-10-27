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

void funkie(int x){
  vector<int> p;
  while (x % 2 == 0) p.push_back(2), x /= 2;
  for (int d=3; 1LL*d*d <= 1LL*x; d += 2){
    while (x % d == 0) p.push_back(d), x /= d;
  }
  if (x > 1) p.push_back(x);

  printf("%d", p[0]);
  for (int i=1; i<p.size(); ++i){
    printf(" x %d", p[i]);
  }
  puts("");
}

int main(){
  int n;
  while (scanf("%d", &n)==1 && n){
    printf("%d = ", n);
    if (n < 0) printf("-1 x "), funkie(-n);
    else funkie(n);
  }
  return 0;
}
