/*
  Problem: G - GATTACA
  Author: Andrés Mejía-Posada
  (http://blogaritmo.factorcomun.org)

  Slow. Takes ~14 seconds on 100 hundred strings of length 1000.
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

inline int v(char c){if(c=='A')return 0;if(c=='C')return 1;if(c=='G')return 2;if(c=='T')return 3;};

struct node{
  int info;
  node * sons[4];
  node(int i = 0) : info(i){ sons[0] = sons[1] = sons[2] = sons[3] = NULL; }
};

void clean(node * &u){
  if (u != NULL){
    for (int i=0; i<4; ++i) clean(u->sons[i]);
    delete u;
    u = NULL;
  }
}

int main(){
  //freopen("gattaca.in", "r", stdin);
  int T;
  cin >> T;
  while (T--){
    string s;
    cin >> s;
    int n = s.size(), rep = 0;
    string ans = "";

    node* root = new node;

    for (int i=0; i<n; ++i){
	node * foot = root; //Tells me where i'm standing.
	string so_far = "";
	so_far.reserve(1000);
	for (int j=i; j < n; ++j){
	  so_far = s.substr(i, j-i+1);
	  if (foot->sons[v(s[j])] == NULL) foot->sons[v(s[j])] = new node;
	  foot = foot->sons[v(s[j])];
	  int t = ++foot->info;
	  if (t > 1 && (so_far.size() > ans.size() || (so_far.size() == ans.size() && so_far < ans))){
	    ans = so_far;
	    rep = t;
	  }
	}
      }
 	   if (rep == 0) cout << "No repetitions found!\n";
	   else cout << ans << " " << rep << endl;
	 clean(root);
  }
  return 0;
}
