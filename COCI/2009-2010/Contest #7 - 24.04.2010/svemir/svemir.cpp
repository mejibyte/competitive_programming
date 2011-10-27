#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

#define D(x) cout << #x " = " << (x) << endl
using namespace std;

struct point {
  int x, y, z;
};

int dist(point &a, point &b){
  int dx = abs(a.x - b.x);
  int dy = abs(a.y - b.y);
  int dz = abs(a.z - b.z);
  return min(dx, min(dy, dz));
}

const int MAXNODES = 100000;
int p[MAXNODES], rank[MAXNODES];
void make_set(int x){ p[x] = x, rank[x] = 0; }
void link(int x, int y){
  if (rank[x] > rank[y]) p[y] = x;
  else{ p[x] = y; if (rank[x] == rank[y]) rank[y]++; }
}
int find_set(int x){
  return x != p[x] ? p[x] = find_set(p[x]) : p[x];
}
void merge(int x, int y){ link(find_set(x), find_set(y)); }


int main(){
  int n;
  cin >> n;
  vector<point> p(n);
  for (int i = 0; i < n; ++i){
    cin >> p[i].x >> p[i].y >> p[i].z;
    make_set(i);
  }
  
  vector< pair<int, pair<int, int> > > edges;
  for (int i = 0; i < n; ++i){
    for (int j = i + 1; j < n; ++j){
      edges.push_back(make_pair( dist(p[i], p[j]), make_pair(i, j)));
    }
  }
  sort(edges.begin(), edges.end());
  int ans = 0;
  for (int i = 0; i < edges.size(); ++i){
    int u = edges[i].second.first;
    int v = edges[i].second.second;
    int w = edges[i].first;
    if (find_set(u) != find_set(v)){
      ans += w;
      merge(u, v);
    }
  }
  cout << ans << endl;

  
  return 0;
}
