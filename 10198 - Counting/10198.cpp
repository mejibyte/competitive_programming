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

#define D(x) cout << #x " is " << x << endl

long long dp[1010];

int main(){
  dp[0] = 1;
  for (int i=0; i<=1000; ++i){
    dp[i+1] += 2*dp[i];
    dp[i+2] += dp[i];
    dp[i+3] += dp[i];
  }
  int n;
  while (cin >> n) cout << dp[n] << endl;
  return 0;
}
