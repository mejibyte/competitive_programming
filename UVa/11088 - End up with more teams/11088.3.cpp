/*
  Problem: 11088 - End up with More Teams
  Author: Andrés Mejía-Posada

  Trying another approach...
  Time-limit exceeded + wrong answer
 */

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
using namespace std;

#define D(x) cout << #x " is " << x << endl
#define bit(i, n) (n & (1 << i))

int x[15], p[15], n, ans;

bool used[15];

void search(int teams, int person, int first){
  //printf("t = %d, p = %d, f = %d\n", teams, person, first);
  //for (int i=0; i<person; ++i) cout << p[i] << " "; cout << endl;
  ans = max(ans, teams);

  for (int i=first; i<n; ++i){
    if (!used[i]){
      p[person] = i;
      used[i] = true;
      if (person % 3 < 2){
	search(teams, person+1, i+1);
      }else if (x[p[person-2]] + x[p[person-1]] + x[i] >= 20){
	search(teams + 1, person+1, p[person-2]);
      }
      used[i] = false;
    }
  }
}

int main(){
  int pizza = 1;
  while (scanf("%d", &n) == 1 && n){
    for (int i = 0; i<n; ++i) scanf("%d", &x[i]);
    sort(x, x+n);
    memset(used, 0, sizeof used);
    search(0, 0, 0);
    printf("Case %d: %d\n", pizza++, ans);
  }

  return 0;
}
