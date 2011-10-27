/*
  Problem: 11385 - Da Vinci Code
  Author: Andrés Mejía-Posada

  Que gonorrea de problema.
 */

using namespace std;
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int fib[50], T, n;
string ans, s;

int main(){
  fib[0] = 1, fib[1] = 2;
  for (int i=2; fib[i-1] + fib[i-2] > 0; ++i) fib[i] = fib[i-1] + fib[i-2];

  for(cin >> T; T--; cout << ans << endl){
    cin >> n;
    vector<int> nums(n);
    for (int i=0; i<n; ++i) cin >> nums[i];

    getline(cin, s), getline(cin, s);
    for (int i=0; i<s.size(); ++i) if (!isupper(s[i])) s.erase(i, 1), i--;

    vector<int> pos(n);
    for (int i=0; i<n; ++i) pos[i] = lower_bound(fib, fib + 50, nums[i]) - fib;

    ans = string(*max_element(pos.begin(), pos.end()) + 1, ' ');

    for (int i=min(s.size(), pos.size()) - 1; i >= 0; --i) ans[pos[i]] = s[i];
  }
  return 0;
}
