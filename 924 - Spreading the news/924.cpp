/*
  Problem: 924 - Spreading the news (UVa Online Judge)
  Andrés Mejía-Posada

  Verdict: Wrong answer
 */
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main(){
  int E;
  scanf("%d", &E);
  vector<int> g[E];
  for (int i=0; i<E; ++i){
    int N;
    scanf("%d", &N);
    while (N--){
      int j;
      scanf("%d", &j);
      g[i].push_back(j);
    }
  }

  int T;
  scanf("%d", &T);
  while (T--){
    int u;
    scanf("%d", &u);
    if (g[u].size() == 0){
      printf("0\n");
    }else{
      int max_boom = 0, first_day = 0, booms[E];
      bool visited[E];
      memset(booms, 0, sizeof booms);
      memset(visited, false, sizeof visited);
      queue<pair<int, int> > q;
      q.push(make_pair(u, 0));
      while (q.size()){
        int person = q.front().first;
        int today = q.front().second;
        q.pop();

        if (visited[person]) continue;

        visited[person] = true;
        booms[today]++;
        if (booms[today] > max_boom){
          max_boom = booms[today];
          first_day = today;
        }

        vector<int> &friends = g[person];
        for (int i=0; i<friends.size(); ++i){
          if (!visited[friends[i]]){
            q.push(make_pair(friends[i], today + 1));
          }
        }
      }
      printf("%d %d\n", max_boom, first_day);
    }
  }
  return 0;
}
