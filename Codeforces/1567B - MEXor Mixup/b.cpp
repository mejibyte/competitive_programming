#include <bits/stdc++.h>

#define D(x) cerr << #x " is " << (x) << endl

using namespace std;

int sequence_xor(int n) {
  if (n % 4 == 0)
    return n;
  if (n % 4 == 1)
    return 1;
  if (n % 4 == 2)
    return n + 1;
  return 0;
}

int solve(int desired_mex, int desired_xor) {
  int _xor = sequence_xor(desired_mex - 1);
  if (_xor == desired_xor) return desired_mex; // len[0, desired_mex-1]
  int remaining = _xor ^ desired_xor;
  if (remaining != desired_mex) {
    return desired_mex + 1;
  }
  return desired_mex + 2;
}

int main() {
  ios::sync_with_stdio(false);
	cin.tie(0);

  int T;
  cin >> T;
  while (T--) {
    int a, b;
    cin >> a >> b;
    cout << solve(a, b) << endl;
  }
  return 0;
}