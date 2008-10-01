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
    int n = s.size();
    bool solved = false;
    map<string, int> cnt;
    for (int d=n-1; d>0; --d){
      cnt.clear();
      for (int i=0, j; (j = i + d) <= n; ++i){
	cnt[s.substr(i, d)]++;
	//cout << s.substr(i, d) << " = " << cnt[s.substr(i, d)] << endl;
      }
      for (map<string, int>::iterator i = cnt.begin(); i != cnt.end(); ++i){
	if (i->second > 1){
	  cout << i->first << " " << i->second << endl;
	  solved = true;
	  d = -1; //end outer loop
	  break;
	}
      }
    }
    if (!solved) cout << "No repetitions found!\n";
  }
  return 0;
}
