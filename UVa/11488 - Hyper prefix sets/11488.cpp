/*
  Time-limit exceeded.

  Problem: 11488 - Hyper prefix sets
  Author: Andrés Mejía-Posada
 */

#include <algorithm>
#include <iterator>
#include <iostream>
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
using namespace std;

int dp[50001][201];
string s[50001];

#define V(x, t, d) copy(x.begin(), x.end(), ostream_iterator<t>(cout, d)); cout << endl

int main(){
  int C;
  cin >> C;
  while (C--){
    int n;
    cin >> n;
    int maxLen = -1;
    for (int i=0; i<n; ++i) cin >> s[i], maxLen = max(maxLen, (int)s[i].length());
    sort(s, s + n);
    
    //V(s, string, "\n");
    
    //for (int i=0; i<n; ++i) for (int j=0; j<=maxLen; ++j) dp[i][j] = 0;
    
    for (int j=0; j<s[0].size(); ++j) dp[0][j] = 1;
    for (int i=1; i<n; ++i) dp[i][0] = 1 + (s[i][0] == s[i-1][0] ? dp[i-1][0] : 0);

    int ans = -1;
    for (int i=1; i<n; ++i){
      for (int j=1, m = s[i].size(); j<m; ++j){
	dp[i][j] = 1;
	if (j < s[i-1].length() && s[i][j] == s[i-1][j] &&
	    dp[i][j-1] > dp[i-1][j-1]){
	  dp[i][j] += dp[i-1][j];
	}
	ans = max(ans, (j+1)*dp[i][j]);
      }
    }

//     for (int i=0; i<n; ++i){
//       for (int j=0; j<maxLen; ++j){
// 	printf("%1d ", dp[i][j]);
//       }
//       cout << endl;
//     }


    cout << ans << endl;
    
  }
  return 0;
}
