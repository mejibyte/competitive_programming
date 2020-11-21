#include <iostream>
#include <vector>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> previous(n+1, -1);
    vector<int> distance(n+1, -1);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
      distance[a[i]] = max(distance[a[i]], i - previous[a[i]]);
      previous[a[i]] = i;
    }
    for (int i = 0; i < n; ++i) {
      distance[a[i]] = max(distance[a[i]], n - previous[a[i]]);
    }

    vector<int> answer(n+1, -1);
    for (int p = 1; p <= n; ++p) {
      int start = distance[p];
      if (start == -1) {
        continue;
      }
      for (int k = start; k <= n and answer[k] == -1; k++) {
        answer[k] = p;
      }
    }
    for (int k = 1; k <= n; ++k) {
      cout << answer[k] << " ";
    }
    cout << endl;
  }
  return 0;
}