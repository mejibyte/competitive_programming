#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

int capacity, n;
vector<int> w;

int dp(int p, int s, int i){
  if (p > capacity || s > capacity)
    return INT_MIN;
  if (i >= n)
    return 0;

  return max(dp(p + w[i], s, i+1) + 1, dp(p, s + w[i], i+1) + 1);

}

int main(){
  int C;
  cin >> C;
  while (C--){
    cin >> capacity;
    capacity *= 100;
    
    w.clear();
    int x;
    while(cin >> x && x){
      w.push_back(x);
    }

    n = w.size();
    
    cout << dp(0,0,0) << endl;
  }
  return 0;
}
