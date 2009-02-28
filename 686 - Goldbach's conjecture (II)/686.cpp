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
#include <list>
#include <map>
#include <set>

#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

const int MAXN =  1 << 15 + 5;
bool prime[MAXN];

int main(){
  memset(prime, true, sizeof prime);
  prime[0] = prime[1] = false;
  for (int i=4; i<MAXN; i += 2) prime[i] = false;
  for (int i=3; i<MAXN; i += 2){
    if (prime[i]){
      for (int j=i+i; j<MAXN; j += i) prime[j] = false;
    }
  }

  int n;
  while (scanf("%d", &n)==1 && n){
    int m = n / 2, ans = prime[n-2];
    for (int a = 3; a <= m; a += 2){
      ans  += (prime[a] && prime[n-a]);
    }
    printf("%d\n", ans);
  }
  return 0;
}
