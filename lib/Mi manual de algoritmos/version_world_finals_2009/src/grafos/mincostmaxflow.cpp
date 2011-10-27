const int MAXN = 105, oo = INT_MAX / 2 - 1;
int cap[MAXN][MAXN];
int cost[MAXN][MAXN];
int flow[MAXN][MAXN];
/* Uso:
  Llenar cap y cost.
  Llenar flow con 0s.
  Invocar la función.
 */
pair<int, int> min_cost_max_flow(int N, int source, int sink)
  { int flowSize = 0; int flowCost = 0; int infinity = 1;
  while (2*infinity > infinity) infinity *= 2;
  // speed optimization #1: adjacency graph
  // speed optimization #2: cache the degrees
  vector<int> deg(N,0); vector<vector<int> > G(N); for (int
  i=0; i<N; i++) for (int j=0; j<i; j++) if (cap[i][j]>0 ||
  cap[j][i]>0) { deg[i]++; deg[j]++; G[i].push_back(j);
  G[j].push_back(i); } vector<int> potential(N,0); while (1) {
    // use dijkstra to find an augmenting path
    vector<int> from(N,-1); vector<int> dist(N,infinity);
    priority_queue< pair<int,int>, vector<pair<int,int> >,
    greater<pair<int,int> > > Q; Q.push(make_pair(0,source));
    from[source]=-2; dist[source] = 0; while (!Q.empty()) {
    int howFar = Q.top().first; int where = Q.top().second;
    Q.pop(); if (dist[where] < howFar) continue; for (int i=0;
    i<deg[where]; i++) { int dest = G[where][i];
      // now there are two possibilities: add flow in
      // the right direction, or remove in the other one
        if (flow[dest][where] > 0) if (dist[dest] >
          dist[where] + potential[where] - potential[dest] -
          cost[dest][where]) { dist[dest] = dist[where] +
          potential[where] - potential[dest] -
          cost[dest][where]; from[dest] = where;
          Q.push(make_pair(dist[dest],dest)); } if
          (flow[where][dest] < cap[where][dest]) if
          (dist[dest] > dist[where] + potential[where] -
          potential[dest] + cost[where][dest]) { dist[dest] =
          dist[where] + potential[where] - potential[dest] +
          cost[where][dest]; from[dest] = where;
          Q.push(make_pair(dist[dest],dest)); }
        // no breaking here, we need the whole graph
      } }
    // update vertex potentials
    for (int i=0; i<N; i++) potential[i] += dist[i];
    // if there is no path, we are done
    if (from[sink] == -1) return make_pair(flowSize,flowCost);
    // construct an augmenting path
    int canPush = infinity; int where = sink; while (1) { int
    prev=from[where]; if (prev==-2) break; if
    (flow[where][prev]) canPush = min( canPush,
    flow[where][prev] ); else canPush = min( canPush,
    cap[prev][where] - flow[prev][where] ); where=prev; }
    // update along the path
    where = sink; while (1) { int prev=from[where]; if
    (prev==-2) break; if (flow[where][prev]) {
    flow[where][prev] -= canPush; flowCost -= canPush *
    cost[where][prev]; } else { flow[prev][where] += canPush;
    flowCost += canPush * cost[prev][where]; } where=prev; }
    flowSize += canPush; } return make_pair(0, oo); }

