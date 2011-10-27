/*
  Problem: 10249 - The grand dinner
  Andrés Mejía-Posada (andmej@gmail.com)

  Accepted
  Greedy
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
#include <list>
#include <map>
#include <set>

#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define D(x) cout << #x " is " << x << endl
#define For(i, a, b) for (int i=(a); i<(b); ++i)

const int MAXN = 135;
vector<int> g[MAXN];

int main(){
  int nteams, ntables;
  while (scanf("%d %d", &nteams, &ntables)==2 && nteams && ntables){
    int people = 0, spots = 0;
    for (int i=0; i<nteams; ++i) g[i].clear();
    vector<pair<int, int> > teams(nteams), tables(ntables);
    for (int i=0, c; i<nteams; ++i){
      scanf("%d", &c);
      teams[i] = make_pair(c, i);
      people += c;
    }
    for (int i=0, c; i<ntables; ++i){
      scanf("%d", &c);
      tables[i] = make_pair(c, i);
      spots += c;
    }
    if (people > spots){ printf("0\n"); continue; }

    int f = 0;
    sort(teams.begin(), teams.end(), greater<pair<int, int> >());
    sort(tables.begin(), tables.end(), greater<pair<int, int> >());
    for (int i=0; i<teams.size(); ++i){
      for (int j=0; j<tables.size() && teams[i].first > 0; ++j){
        if (tables[j].first > 0){
          teams[i].first--;
          tables[j].first--;
          g[teams[i].second].push_back(tables[j].second);
          ++f;
        }
      }
    }

    if (f < people){
      printf("0\n");
    }else{
      printf("1\n");
      for (int i=0; i<nteams; ++i){
        bool first = true;
        foreach(v, g[i]){
          int j = *v;
          if (!first) printf(" ");
          first = false;
          printf("%d", j+1);
        }
        printf("\n");
      }
    }
  }
  return 0;
}
