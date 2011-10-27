/*
  Accepted, slower.
 */
#include <iostream>
#include <cassert>
#include <queue>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

struct state{
  int i, lights, w;
  vector<string> path;
  state() {}
  state(int I, int L, int W) : i(I), lights(L), w(W) {}
};

const int MAXR = 10;

int toggleBit(int x, int b){
  if (x & (1 << b))
    return x & ~(1 << b);
  else
    return x | (1 << b);
}

int differentBit(int x, int y){
  return __builtin_ctz(x ^ y);
}

int main(){
  int r, d, s, C = 1;
  while (scanf("%d%d%d", &r, &d, &s) == 3 && (r+d+s)){
    vector<int> doors[r], switches[r];
    printf("Villa #%d\n", C++);

    for (int i=0; i<d; ++i){
      int u, v;
      scanf("%d%d", &u, &v);
      --u, --v;
      doors[u].push_back(v);
      doors[v].push_back(u);
    }

    for (int i=0; i<s; ++i){
      int u, v;
      scanf("%d%d", &u, &v);
      --u, --v;
      switches[u].push_back(v);
    }

    bool visited[(1<<MAXR)+1][MAXR] = {false};

    queue<state> q;
    q.push(state(0, 1<<0, 0));
    bool solved = false;
    while (q.size()){
      state u = q.front();
      //printf("popped state: i = %d, lights = %X, w = %d\n", u.i, u.lights, u.w);
      q.pop();
      if (u.i == r - 1 && u.lights == (1 << (r-1))){
        //Solution found
        solved = true;
        //printf("u.path.size() = %d, u.w = %d\n", u.path.size(), u.w);
        assert(u.path.size() == u.w);
        //printf("Solution found. i = %d, lights = %X, w = %d\n", u.i, u.lights, u.w);
        printf("The problem can be solved in %d steps:\n", u.w);
        copy(u.path.begin(), u.path.end(), ostream_iterator<string>(cout, ""));
        break;
      }

      if (visited[u.lights][u.i]) continue;
      visited[u.lights][u.i] = true;

      vector<int> &s = switches[u.i];
      for (int j=0; j<s.size(); ++j){
        int nlights = toggleBit(u.lights, s[j]);
        if (!visited[nlights][u.i] && (nlights & (1 << u.i))){
          q.push(state(u.i, nlights, u.w + 1));
          char buf[256];
          sprintf(buf, "- Switch %s light in room %d.\n", (nlights > u.lights ? "on" : "off"), differentBit(u.lights, nlights) + 1);
          q.back().path = u.path;
          q.back().path.push_back(string(buf));
          //printf("  pushed state: i = %d, lights = %X, w = %d\n", u.i, nlights, u.w + 1);
        }
      }

      vector<int> &d = doors[u.i];
      for (int j=0; j<d.size(); ++j){ //Moverme sin apagar luces
        if (!visited[u.lights][d[j]] && (u.lights & (1 << d[j]))){
          q.push(state(d[j], u.lights, u.w + 1));
          char buf[256];
          sprintf(buf, "- Move to room %d.\n", d[j] + 1);
          //printf("  pushed state: i = %d, lights = %X, w = %d\n", d[j], u.lights, u.w + 1);
          q.back().path = u.path;
          q.back().path.push_back(string(buf));
        }
      }
    }

    if (!solved) printf("The problem cannot be solved.\n");
    printf("\n");
  }
  return 0;
}
