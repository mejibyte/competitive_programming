#include <iostream>
#include <cassert>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const int MAXSUM = 200;
const int MAXCOINS = 20;
//dp[i][j] = verdadero si puedo repartir las primeras i monedas en dos grupos que difieran en j
bool dp[MAXCOINS][MAXSUM+1];

int main(){
  int runs;
  string s;
  cin >> runs;
  getline(cin, s);
  while (runs--){
    memset(dp, false, sizeof dp);
    getline(cin, s);
    stringstream sin(s);
    int n, x, sum;
    n = sum = 0;
    vector<int> m;
    while (sin >> x){
      ++n, m.push_back(x), sum += x;
    }
    assert(n == m.size());

    dp[0][m[0]] = true;
    for (int i=1; i<n; ++i){
      for (int j=0; j<=sum; ++j){
        dp[i][j] = dp[i-1][abs(j - m[i])];
        if (j + m[i] <= sum){
          dp[i][j] |= dp[i-1][j + m[i]];
        }
      }
    }
    cout << (dp[n-1][0]?"YES":"NO") << endl;
  }
  return 0;
}

