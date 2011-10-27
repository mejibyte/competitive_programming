/*
  Problem:
  Andrés Mejía-Posada (andmej@gmail.com)
 */
using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <numeric>
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

int dp[1005];
bool good[1005][1005];


int main(){
  int cases;
  cin >> cases;
  string s;
  while (cases--){
    cin >> s;
    s = " " + s;
    int n = s.size();

    for (int i=0; i<n; ++i){
      good[i][i] = true;
      if (i + 1 < n){
        good[i][i+1] = s[i] == s[i+1];
      }
    }
    for (int d=2; d<=n; ++d){
      for (int i=0, j; (j = i + d)<n; ++i){
        good[i][j] = good[i+1][j-1] && (s[i] == s[j]);
      }
    }

    dp[0] = 0;
    for (int i=1; i<n; ++i){
      dp[i] = n + 5;
      string t = "";
      for (int j=i; j>0; --j){
        t += s[j];
        if (good[j][i]){
          dp[i] = min(dp[i], dp[j-1] + 1);
        }
      }
    }
    cout << dp[n-1] << endl;
  }
  return 0;
}
