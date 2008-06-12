#include <iostream>
#include <cmath>
#include <map>
#include <queue>
#include <set>

using namespace std;

typedef pair<double, double> point;
//Gives a vector of adjacent nodes to a point
typedef map< point, vector<point> > graph;
//Edge of length "first" that arrives to point "second"
typedef pair<double, point> edge; 

double euclidean(const point &a, const point &b){
  return hypot(a.first-b.first, a.second-b.second);
}


int main(){
  int casos;
  cin >> casos;
  while (casos--){
    graph g;
    int n;
    cin >> n;
    while (n--){
      double x,y;
      cin >> x >> y;
      point p(x,y);
      if (g.count(p) == 0){ //Si no está todavía
	vector<point> v;
	g[p] = v;
	for (graph::iterator i = g.begin(); i != g.end(); ++i){
	  if ((*i).first != p){
	    (*i).second.push_back(p);
	    g[p].push_back((*i).first);
	  }
	}
      }
    }

    set<point> visited;
    priority_queue<edge, vector<edge>, greater<edge> > q;
    //Each edge in q has got a length "first" and a point "second".
    //It means I can reach point "second" which is "first" meters away.
    //q has the closest reachable node on top (I may have already visited it!)
    q.push(edge(0.0, (*g.begin()).first));
    double totalDistance = 0.0;
    while (!q.empty()){
      edge nearest = q.top();
      q.pop();
      point actualNode = nearest.second;
      if (visited.count(actualNode) == 1) continue; //Ya habia visitado este
      totalDistance += nearest.first;
      visited.insert(actualNode);
      vector<point> neighbors = g[actualNode];
      for (int i=0; i<neighbors.size(); ++i){
	point t = neighbors[i];
	double dist = euclidean(actualNode, t);
	q.push(edge(dist, t));
      }
    }
    printf("%.2f\n", totalDistance);
    if (casos > 0) cout << endl; //Endl between cases
  }
}
