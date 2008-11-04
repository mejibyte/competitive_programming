/*
  Problem: 120 - Stack of flapjacks
  Author: Andrés Mejía-Posada
  (http://blogaritmo.factorcomun.org)

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

  string s;
  while (getline(cin, s)){
    stringstream sin(s);

    vector<int> v, sol;
    for (int x; sin >> x; v.push_back(x), sol.push_back(x));
    sort(sol.begin(), sol.end(), greater<int>());

    cout << v[0];
    for (int i=1; i<v.size(); ++i) cout << " " << v[i];
    cout << endl;

    reverse(v.begin(), v.end());

    int n = v.size();

    int llevo = 0;
    while (llevo < n){
      int i=llevo;
      while (v[i] != sol[llevo]) ++i;
      if (i > llevo){
        if (i+1 < n) cout << i+1 << " ";
        reverse(v.begin()+i, v.end());
        if (llevo+1 < n) cout << llevo+1 << " ";
        reverse(v.begin()+llevo, v.end());
      }
      llevo++;
    }
    cout << "0\n";
  }
  return 0;
}
