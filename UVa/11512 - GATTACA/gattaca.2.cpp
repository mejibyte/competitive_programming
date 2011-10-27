/*
  Problem: G - GATTACA
  Author: Andrés Mejía-Posada
  (http://blogaritmo.factorcomun.org)

  Naive
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

int main(){
  //freopen("gattaca.in", "r", stdin);
  int T;
  cin >> T;
  while (T--){
    string s;
    cin >> s;
    int n = s.size(), rep = 0;
    string ans = "";
    map<string, int> cnt;
    for (int i=0; i<n; ++i){
	string so_far = "";
	for (int j=i; j < n; ++j){
	  so_far += s[j];
	  int t = ++cnt[so_far]; 
	  if (t > 1 && (so_far.size() > ans.size() || (so_far.size() == ans.size() && so_far < ans))){
	    ans = so_far;
	    rep = t;
	  }
	}
      }
 	   if (rep == 0) cout << "No repetitions found!\n";
	   else cout << ans << " " << rep << endl;
  }
  return 0;
}
