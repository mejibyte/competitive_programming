/*
  Problem: 11385 - Da Vinci Code
  Author: Andrés Mejía-Posada

  Que gonorrea de problema.

  Accepted.
 */

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

vector<int> fib;

int binary_search(int what, const vector<int> &where){
  int n = where.size();
  int low = 0, high = n - 1;
  while (low < high){
    int mid = (low + high) / 2;
    if (where[mid] < what){
      low = mid + 1;
    }else{
      high = mid;
    }
  }
  if (where[low] != what) return -1;
  return low;
}

int main(){
  fib.push_back(1);
  fib.push_back(2);
  while (fib[fib.size()-1] + fib[fib.size()-2] > 0){ //Before overflow
    fib.push_back(fib[fib.size()-1] + fib[fib.size()-2]);
  }

  int T;
  for(cin >> T; T--; ){
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i=0; i<n; ++i) cin >> nums[i];

    string s;
    getline(cin, s);
    getline(cin, s);
    for (int i=0; i<s.size(); ++i)
      if (!isupper(s[i])){
        s.erase(i, 1);
        i--;
      }

    vector<int> pos(n);
    for (int i=0; i<n; ++i){
      pos[i] = binary_search(nums[i], fib);
    }

    string ans( *(max_element(pos.begin(), pos.end())) + 1, ' ');

    for (int i=min(s.size(), pos.size()) - 1; i >= 0; --i){
      ans[pos[i]] = s[i];
    }

    cout << ans << endl;

  }

  return 0;
}
