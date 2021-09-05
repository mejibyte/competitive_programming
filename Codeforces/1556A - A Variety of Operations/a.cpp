#include <bits/stdc++.h>

using namespace std;

int solve(int a, int b) {
  if (a == 0 and b == 0) return 0;
  if ((a - b) % 2 != 0) return -1;
  if (a == b) return 1;
  return 2;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    int a, b;
    cin >> a >> b;
    cout << solve(a, b) << endl;
  }
  return 0;
}
