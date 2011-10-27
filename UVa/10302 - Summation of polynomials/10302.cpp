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
#define D(x) cout << #x " is " << x << endl

const int MAXN = 50000;
long long s[MAXN+1];

int main(){
  s[0] = 0;
  for (long long i=1; i<=MAXN; ++i){
    s[i] = s[i-1] + i*i*i;
  }

  int n;
  while (scanf("%d", &n)) printf("%lld\n", s[n]);

  return 0;
}
