/*
  Problem: C -Life on Mars?
  Author: Andrés Mejía-Posada
  (http://blogaritmo.factorcomun.org)

  Accepted
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
  //assert(freopen("life.in", "r", stdin) != NULL);
  string line;
  while (getline(cin, line) && line != "0"){
    vector<int> s;
    int x, n;
    stringstream sin(line);
    while (sin >> x) s.push_back(x);
    n = s.size();
    bool valid = true;
    vector<int> t(n, -1);
    for (int i=0; i<n; ++i){
      if (s[i] >= n){
	cout << "Message hacked by the Martians!!!\n";
	valid = false;
      }
    }
    if (valid){
      for (int i=0; i<s.size(); ++i){
	if (t[s[i]] == -1){
	  t[s[i]] = s[i];
	  s.erase(s.begin() + i);
	  --i;
	}
      }
      for (int i=0; i<n; ++i){
	if (t[i] != -1) cout << (i>0?" ":"") << t[i];
	else (cout << (i>0?" ":"") << s[0]), s.erase(s.begin());
      }
      cout << endl;
    }
  }
  return 0;
}
