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

template <class T> string toStr(const T &x){ stringstream s; s << x; return s.str(); }
template <class T> int toInt(const T &x){ stringstream s; s << x; int r; s >> r; return r; }

#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define D(x) cout << #x " is " << x << endl

const int MAXN = 505, oo = 1000000000;
bool fire[MAXN];
int g[MAXN][MAXN];

int main(){
  string s;
  int casos;
  getline(cin, s);
  casos = toInt(s);
  getline(cin, s);
  while (casos--){
    string input;
    while (getline(cin, s) && s != ""){
      input += " " + s;
    }
    stringstream sin(input);

    int f, n;
    sin >> f >> n;
    For(i, 0, n){
      fire[i] = 0;
      For(j, 0, n){
        g[i][j] = oo;
      }
      g[i][i] = 0;
    }
    For(k, 0, f){
      int u;
      sin >> u;
      fire[--u] = true;
    }
    int u, v, w;
    while (sin >> u >> v >> w){
      --u, --v;
      g[u][v] = min(g[u][v], w);
      g[v][u] = min(g[v][u], w);
    }

    For(k, 0, n){
      For(i, 0, n){
        For(j, 0, n){
          g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
        }
      }
    }

    /*
    For(i, 0, n){
      For(j, 0, n){
        printf("%d ", g[i][j]);
      }
      puts("");
    }
    */

    int which = 0, howmuch = oo;
    For(i, 0, n){
      if (fire[i]) continue;
      //printf("trying to place a station at %d\n", i);
      fire[i] = true;
      int distance = -1;
      For(j, 0, n){
        int cur = oo;
        For(k, 0, n){
          if (fire[k]){
            cur = min(cur, g[j][k]);
          }
        }
        //printf("  closest station from node %d is at %d\n", j, cur);
        distance = max(distance, cur);
      }
      if (distance < howmuch){
        which = i;
        howmuch = distance;
      }
      fire[i] = false;
    }
    cout << which + 1 << endl;
    if (casos > 0) cout << endl;
  }
  return 0;
}
