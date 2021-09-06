#include <bits/stdc++.h>

using namespace std;

long long dp[35][2][2];

void solve(int num) {
  vector<int> digits;
  for (int x = num; x > 0; x /= 10) {
    digits.push_back(x % 10);
  }
  for (int i = 0; i <= digits.size(); ++i) {
    for (int c = 0; c < 2; c++) {
      for (int cc = 0; cc < 2; cc++) {
        dp[i][c][cc] = 0;
      }
    }
  }

  dp[0][0][0] = 1LL;
  for (int i = 0; i < digits.size(); ++i) {
    for (int c = 0; c < 2; c++) {
      for (int cc = 0; cc < 2; cc++) {

        for (int d1 = 0; d1 <= 9; d1++) {
          for (int d2 = 0; d2 <= 9; d2++) {
            int got = d1 + d2 + c;
            if (got % 10 != digits[i]) {
              continue;
            }

            int new_c = cc;
            int new_cc = got / 10;

            dp[i+1][new_c][new_cc] += dp[i][c][cc];
          }
        }
      }
    }
  }

  cout << dp[digits.size()][0][0] - 2 << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int T;
  cin >> T;
  while (T--) {
    int num;
    cin >> num;
    solve(num);
  }
  return 0;
}