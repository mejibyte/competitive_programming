/*
  ACRush's Dinic algorithm for maximum flow
  Complexity: O(E V^2)

  Usage:
  init(number of nodes, source, sink);
  Create graph using add_edge(int u, int v, int c1, int c2):
  This adds two directed edges: u -> v with capacity c1
    and v -> u with capacity c2.
  c2 by default is 0.
  After creating the graph, nedge contains the number of
     total edges.
  dinic_flow();
  This doesn't modify the capacity of the original graph,
     so you can run the algorithm several times on the same
     graph.
  If you want to run the algorithm with different sources/sinks
     assign the correct value to src and dest before calling
     dinic_flow().
 */

const int maxnode=2*55 + 5; const int
maxedge=maxnode*(maxnode-1)/2; const int oo=1000000000;

int node,src,dest,nedge; int
head[maxnode],point[maxedge],next[maxedge],
flow[maxedge],capa[maxedge];
int dist[maxnode],Q[maxnode],work[maxnode];

void init(int _node,int _src,int _dest) { node=_node;
src=_src; dest=_dest; for (int i=0;i<node;i++) head[i]=-1;
nedge=0; } void add_edge(int u,int v,int c1,int c2 = 0) {
point[nedge]=v,capa[nedge]=c1,flow[nedge]=0,
next[nedge]=head[u],head[u]=(nedge++);
point[nedge]=u,capa[nedge]=c2,flow[nedge]=0,
next[nedge]=head[v],head[v]=(nedge++);
} bool dinic_bfs() { memset(dist,255,sizeof(dist));
dist[src]=0; int sizeQ=0; Q[sizeQ++]=src; for (int
cl=0;cl<sizeQ;cl++) for (int k=Q[cl],i=head[k];i>=0;i=next[i])
if (flow[i]<capa[i] && dist[point[i]]<0) {
dist[point[i]]=dist[k]+1; Q[sizeQ++]=point[i]; } return
dist[dest]>=0; } int dinic_dfs(int x,int exp) { if (x==dest)
return exp; for (int &i=work[x];i>=0;i=next[i]) { int
v=point[i],tmp; if (flow[i]<capa[i] && dist[v]==dist[x]+1 &&
(tmp=dinic_dfs(v,min(exp,capa[i]-flow[i])))>0) { flow[i]+=tmp;
flow[i^1]-=tmp; return tmp; } } return 0; } int dinic_flow() {
for (int i=0; i<nedge; ++i) flow[i] = 0; int result=0; while
(dinic_bfs()) { for (int i=0;i<node;i++) work[i]=head[i];
while (1) { int delta=dinic_dfs(src,oo); if (delta==0) break;
result+=delta; } } return result; }
