//http://acmicpc-live-archive.uva.es/nuevoportal/data/problem.php?p=2197

// another fine solution by misof
// #includes {{{
#include <algorithm>
#include <numeric>
 
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
 
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cassert>
 
#include <cmath>
#include <complex>
using namespace std;
// }}}
 
/////////////////// PRE-WRITTEN CODE FOLLOWS, LOOK DOWN FOR THE SOLUTION ////////////////////////////////
 
// pre-written code {{{
#define CLEAR(t) memset((t),0,sizeof(t))
#define FOR(i,a,b) for(int i=(int)(a);i<=(int)(b);++i)
typedef pair<int,int> PII;
#define REP(i,n) for(int i=0;i<(int)(n);++i)
#define SIZE(t) ((int)((t).size()))
// }}}
 
/////////////////// CODE WRITTEN DURING THE COMPETITION FOLLOWS ////////////////////////////////
#define MX 200
int CAP[MX][MX];
int COST[MX][MX];
int flow[MX][MX];
 
PII MC_MAXFLOW(int N, int source, int sink) {
  int flowSize = 0;
  int flowCost = 0;
  int infinity = 1; while (2*infinity > infinity) infinity *= 2; 
  
  // speed optimization #1: adjacency graph
  // speed optimization #2: cache the degrees
  vector<int> deg(N,0);
  vector<vector<int> > G(N);
  for (int i=0; i<N; i++) for (int j=0; j<i; j++) if (CAP[i][j]>0 || CAP[j][i]>0) { 
    deg[i]++;
    deg[j]++;
    G[i].push_back(j); G[j].push_back(i);
  }
 
  vector<int> potential(N,0);
 
  while (1) {
    // use dijkstra to find an augmenting path
    vector<int> from(N,-1);
    vector<int> dist(N,infinity);
    
    priority_queue< pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > Q;
    Q.push(make_pair(0,source));
    from[source]=-2; dist[source] = 0;
 
    while (!Q.empty()) {
      int howFar = Q.top().first; 
      int where = Q.top().second;
      Q.pop();
 
      if (dist[where] < howFar) continue;
      
      for (int i=0; i<deg[where]; i++) {
        int dest = G[where][i];
        
        // now there are two possibilities: add flow in the right direction, or remove in the other one
        if (flow[dest][where] > 0)
          if (dist[dest] > dist[where] + potential[where] - potential[dest] - COST[dest][where]) {
            dist[dest] = dist[where] + potential[where] - potential[dest] - COST[dest][where];
            from[dest] = where;
            Q.push(make_pair(dist[dest],dest));
          }
        
        if (flow[where][dest] < CAP[where][dest])
          if (dist[dest] > dist[where] + potential[where] - potential[dest] + COST[where][dest]) {
            dist[dest] = dist[where] + potential[where] - potential[dest] + COST[where][dest];
            from[dest] = where;
            Q.push(make_pair(dist[dest],dest));
          }
 
        // no breaking here, we need the whole graph
      }
    }
 
    // update vertex potentials
    for (int i=0; i<N; i++) potential[i] += dist[i];
 
    // if there is no path, we are done
    if (from[sink] == -1) return make_pair(flowSize,flowCost);
 
    // construct an augmenting path
    int canPush = infinity;
    int where = sink;
 
    while (1) { 
      int prev=from[where]; 
      if (prev==-2) break; 
      if (flow[where][prev]) 
        canPush = min( canPush, flow[where][prev] );
      else 
        canPush = min( canPush, CAP[prev][where] - flow[prev][where] );
      where=prev;
    }
 
    // update along the path
    where = sink;
 
    while (1) { 
      int prev=from[where]; 
      if (prev==-2) break; 
      if (flow[where][prev]) {
        flow[where][prev] -= canPush;
        flowCost -= canPush * COST[where][prev];
      } else {
        flow[prev][where] += canPush;
        flowCost += canPush * COST[prev][where];
      }
      where=prev;
    }
    flowSize += canPush;
  }
  return make_pair(-1,47);
}
int main(){
	int N, M, K;
	int k;
	int casos = 0;
	scanf("%i", &casos);
	for(int h  = 0; h< casos;h++){
		scanf("%i %i %i", &N, &M, &K);
		CLEAR(CAP), CLEAR(COST), CLEAR(flow);
		FOR(i, 1, N)  CAP[0][i] = K;
		FOR(j, N+1, 2*N) CAP[j][2*N+1] = K;
		FOR(i, 1, N)FOR(j, N+1, 2*N) CAP[i][j] = 1;
		
		
// 		printf("%i %i %i\n", N, M, K);
 		FOR(i, 1, N)FOR(j, N+1, 2*N) COST[i][j] = 50000;
		
		for(int i=0;i<M;i++){
			int f, t, d;
			scanf("%i %i %i", &f, &t, &d);
			f++, t++;
			COST[f][t+N] = d ; 
		}
		pair<int, int> p = MC_MAXFLOW(2*N+2, 0, 2*N+1);
		if( p.first != K*N || p.second >= 50000) printf("-1\n");
		else printf("%i\n", p.second);
// 		printf("              %i %i\n", p.first, p.second);
	}
	return 0;
}
