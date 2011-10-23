/////////////// Maximum flow for sparse graphs ///////////////
///////////////    Complexity: O(V * E^2)      ///////////////

/*
  Usage:
  Call initialize_max_flow();
  Create graph using add_edge(u, v, c);
  max_flow(source, sink);

  WARNING: The algorithm writes on the cap array. The capacity
  is not the same after having run the algorithm.  If you need
  to run the algorithm several times on the same graph, backup
  the cap array.
 */

namespace Flow {
    // Maximum number of nodes
    const int MAXN = 100;
    // Maximum number of edges
    // IMPORTANT: Remember to consider the backedges. For
    // every edge we actually need two! That's why we have
    // to multiply by two at the end.
    const int MAXE = MAXN * (MAXN + 1) / 2 * 2; 
    const int oo = INT_MAX / 4;
    int first[MAXN];
    int next[MAXE];
    int adj[MAXE];
    int cap[MAXE];
    int current_edge;

    /*
      Builds a directed edge (u, v) with capacity c.
      Note that actually two edges are added, the edge
      and its complementary edge for the backflow.
     */
    int add_edge(int u, int v, int c){
      adj[current_edge] = v;
      cap[current_edge] = c;
      next[current_edge] = first[u];
      first[u] = current_edge++;

      adj[current_edge] = u;
      cap[current_edge] = 0;
      next[current_edge] = first[v];
      first[v] = current_edge++;
    }

    void initialize_max_flow(){
      current_edge = 0;
      memset(next, -1, sizeof next);
      memset(first, -1, sizeof first);
    }

    int q[MAXN];
    int incr[MAXN];
    int arrived_by[MAXN];
    //arrived_by[i] = The last edge used to reach node i
    int find_augmenting_path(int src, int snk){
      /*
        Make a BFS to find an augmenting path from the source
        to the sink.  Then pump flow through this path, and
        return the amount that was pumped.
      */
      memset(arrived_by, -1, sizeof arrived_by);
      int h = 0, t = 0;
      q[t++] = src;
      arrived_by[src] = -2;
      incr[src] = oo;
      while (h < t && arrived_by[snk] == -1){ //BFS
        int u = q[h++];
        for (int e = first[u]; e != -1; e = next[e]){
          int v = adj[e];
          if (arrived_by[v] == -1 && cap[e] > 0){
            arrived_by[v] = e;
            incr[v] = min(incr[u], cap[e]);
            q[t++] = v;
          }
        }
      }

      if (arrived_by[snk] == -1) return 0;

      int cur = snk;
      int neck = incr[snk];
      while (cur != src){
        //Remove capacity from the edge used to reach
        //node "cur", and add capacity to the backedge
        cap[arrived_by[cur]] -= neck;
        cap[arrived_by[cur] ^ 1] += neck;
        //move backwards in the path
        cur = adj[arrived_by[cur] ^ 1];
      }
      return neck;
    }

    int max_flow(int src, int snk){
      int ans = 0, neck;
      while ((neck = find_augmenting_path(src, snk)) != 0){
        ans += neck;
      }
      return ans;
    }
}