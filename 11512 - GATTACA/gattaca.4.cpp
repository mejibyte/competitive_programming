/*
  Problem: G - GATTACA
  Author: Andrés Mejía-Posada
  (http://blogaritmo.factorcomun.org)

  Fast. Takes 0.5 seconds on 100 hundred strings of length 1000.

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

int main(){
  //freopen("gattaca.in", "r", stdin);
  int T;
  cin >> T;
  while (T--){
    string s;
    cin >> s;
    int n = s.size(), rep = 0;
    string ans = "";

    vector<string> sufijos;
    string t = s;
    sufijos.push_back(t);
    while (t.size() > 0) t.erase(t.begin()), sufijos.push_back(t);
    sort(sufijos.begin(), sufijos.end());
    for (int k=1; k<sufijos.size(); ++k){
      int i;
      for (i=0; i<sufijos[k].size() && i < sufijos[k-1].size() && sufijos[k][i] == sufijos[k-1][i]; ++i);
      if (i > 0){
	t = sufijos[k].substr(0, i);
	if (t == ans) ++rep;
	else if (i > ans.size() || (i == ans.size() && t < ans)) ans = t, rep = 2;
      }
     
    }

    //for (int i=0; i<sufijos.size(); ++i) cout << sufijos[i] << endl;

    if (ans.empty()) cout << "No repetitions found!\n";
    else cout << ans << " " << rep << endl;
  }
  return 0;
}
