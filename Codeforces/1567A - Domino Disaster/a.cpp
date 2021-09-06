#include <bits/stdc++.h>

using namespace std;

void solve(const string& s) {
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == 'L' or s[i] == 'R') cout << s[i];
    if (s[i] == 'D') cout << 'U';
    if (s[i] == 'U') cout << 'D';
  }
  cout << endl;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    string s;
    cin >> s;
    solve(s);
  }
  return 0;
}