/*
  Problem:
  Andrés Mejía-Posada (andmej@gmail.com)
*/
using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <numeric>
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
#include <list>
#include <map>
#include <set>

#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl


int main(){
  int n;
  cin >> n;
  string s;
  getline(cin, s);
  while (n--){
    map<char, int> f;
    getline(cin, s);
    for (int i=0; i<s.size(); ++i){
      s[i] = tolower(s[i]);
      if (isalpha(s[i])) f[s[i]]++;
    }
    int best = 0;
    string ans = "*";
    for (map<char, int>::iterator i = f.begin(); i != f.end(); ++i){
      if(i->second > best){
        best = i->second;
        ans = string(1, i->first);
      }
      else if (i->second == best){
        ans += i->first;
      }
    }
    sort(ans.begin(), ans.end());
    cout << ans << endl;
  }

  return 0;
}
