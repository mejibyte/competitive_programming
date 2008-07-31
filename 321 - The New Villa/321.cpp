/*
  Accepted
 */
#include <iostream>
#include <cassert>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct state{
  int i, lights, w;
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
    state p[(1<<MAXR)+1][MAXR];
    for (int i=0; i<=(1<<MAXR); ++i){
      for (int j=0; j<MAXR; ++j){
        p[i][j] = state(-1, -1, -1);
      }
    }

    queue<state> q;
    int length = -1;
    q.push(state(0, 1<<0, 0));
    while (q.size()){
      state u = q.front();
      //printf("popped state: i = %d, lights = %X, w = %d\n", u.i, u.lights, u.w);
      q.pop();
      if (u.i == r - 1 && u.lights == (1 << (r-1))){
        //Solution found
        //printf("Solution found. i = %d, lights = %X, w = %d\n", u.i, u.lights, u.w);
        length = u.w;
        break;
      }

      if (visited[u.lights][u.i]) continue;
      visited[u.lights][u.i] = true;

      vector<int> &s = switches[u.i];
      for (int j=0; j<s.size(); ++j){
        int nlights = toggleBit(u.lights, s[j]);
        if (!visited[nlights][u.i] && (nlights & (1 << u.i))){
          q.push(state(u.i, nlights, u.w + 1));
          if (p[nlights][u.i].i == -1) p[nlights][u.i] = u;
          //printf("  pushed state: i = %d, lights = %X, w = %d\n", u.i, nlights, u.w + 1);
        }
      }

      vector<int> &d = doors[u.i];
      for (int j=0; j<d.size(); ++j){ //Moverme sin apagar luces
        if (!visited[u.lights][d[j]] && (u.lights & (1 << d[j]))){
          q.push(state(d[j], u.lights, u.w + 1));
          if (p[u.lights][d[j]].i == -1) p[u.lights][d[j]] = u;
          //printf("  pushed state: i = %d, lights = %X, w = %d\n", d[j], u.lights, u.w + 1);
        }
      }
    }
    if (length == -1){
      printf("The problem cannot be solved.\n");
    }else{
      printf("The problem can be solved in %d steps:\n", length);
      vector<state> w;
      state u = state(r-1, 1<<(r-1), -1);
      while (p[u.lights][u.i].i != -1){
        w.insert(w.begin(), u);
        u = p[u.lights][u.i];
      }
      w.insert(w.begin(), u);
      /*
      for (int i=0; i<w.size(); ++i){
        printf(" state: i = %d, lights = %X, w = %d\n", w[i].i, w[i].lights, w[i].w);
        }*/
      fprintf(stderr, "w.size() = %d, length = %d\n", w.size(), length);
      assert(w.size() == length+1);
      for (int i=1; i<w.size(); ++i){
        if (w[i].i != w[i-1].i){
          printf("- Move to room %d.\n", w[i].i + 1);
        }else{
          printf("- Switch %s light in room %d.\n", (w[i-1].lights < w[i].lights ? "on" : "off"), differentBit(w[i-1].lights, w[i].lights) + 1);
        }
      }
    }
    printf("\n");
  }
  return 0;
}
