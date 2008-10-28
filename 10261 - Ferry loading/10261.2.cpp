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

/*
  dp[i][j] = Verdadero si puedo repartir los primeros i carros en orden tal que en el port haya j centímetros usados.
  (El Starboard tendría entonces sum[i] - j unidades usadas)
*/
bool dp[205][10005];
int choice[205][10005], w[205], sum[205];

int main(){

  int C;
  cin >> C;
  bool print_stupid_empty_line = false;

  while(C--){
    if (print_stupid_empty_line) cout << endl;
    print_stupid_empty_line = true;

    int length;
    cin >> length;
    length *= 100;

    int n = 1;
    w[0] = sum[0] = 0;
    for (int x; cin >> x && x; ){
      if (n <= 200){
        w[n] = x;
        sum[n] = sum[n-1] + w[n];
        ++n;
      }
    }
    --n;

    pair<int, int> ans;

    memset(dp, 0, sizeof dp);
    memset(choice, -1, sizeof choice);

    dp[0][0] = true;
    for (int i=0; i<n; ++i){
      for (int j=0; j<=length; ++j){
        if (dp[i][j]){
          if ((j + w[i+1]) <= length){
            dp[i+1][j + w[i+1]] = true;
            choice[i+1][j + w[i+1]] = 1;
            ans = make_pair(i+1, j + w[i+1]);
          }

          if ((sum[i] - j + w[i+1]) <= length){
            dp[i+1][j] = true;
            choice[i+1][j] = 0;
            ans = make_pair(i+1, j);
          }
        }
      }
    }

    cout << ans.first << endl;
    string output = "";
    for (int i=ans.first, j=ans.second; i>0 && choice[i][j] != -1; --i){
      output = (choice[i][j] ? "port\n" : "starboard\n" ) + output;
      if (choice[i][j]) j -= w[i];
    }
    cout << output;

  }
  return 0;
}
