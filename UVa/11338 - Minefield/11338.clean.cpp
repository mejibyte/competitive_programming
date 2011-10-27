#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cmath>
#include <sstream>
#include <functional>

using namespace std;

const double infinity = 1E20;

//I'm representing a node as a point with X and Y coordinates.
struct point{
  double x, y;
  point(double X, double Y){ x = X; y = Y;}
};

//This map holds the best distance seen from the start node in Dijkstra's algorithm
map< point, double > dist;

//Some operator for the points
bool operator ==(const point &a, const point &b){ return (a.x == b.x && a.y == b.y);}
bool operator !=(const point &a, const point &b){ return !(a == b);}
bool operator <(const point &a, const point &b){ return (a.x < b.x || (a.x == b.x && a.y < b.y));}
//This returns the Euclidean distance between two points
double euclidean(point a, point b){return hypot(a.y-b.y, a.x-b.x);}


//This is used as a "sort class" for the priority_queue used by Dijkstra's algorithm.
//It simply sorts the points in the priority_queue by less dist[x].
//i.e, the top of the priority_queue always has the point with smaller dist.
struct heapCompare : public binary_function<point, point, bool>
{
  bool operator()(const point &x, const point &y) const
  { return dist[x] > dist[y]; }
};


struct graph{
  //This holds ALL nodes without relating them to their neighbors, i.e, all nodes alone
  //This is used to keep track of what nodes are present in the map neigbors.
  vector<point> nodes;

  //This holds a vector of all adjacent points for a given point
  //Adjacent points of a point X are those who are not further than 1.5 from X
  map< point, vector<point> > neighbors;

  //This function inserts a new node into the graph.
  void insert(const point &a){
    //First check if the node is allready present.
    if (find(nodes.begin(), nodes.end(), a) != nodes.end()) return;
    //Insert the node
    nodes.push_back(a);
    //Now we are going to insert it as a neighbor of all other nodes with are at most 1.5 away from him
    for (int i=0; i<nodes.size(); ++i){
      //A node can't be neighbor of himself:
      if (nodes[i] != a){
	vector<point> adj = neighbors[nodes[i]];
	//Make sure the node hasn't been inserted before.
	//In theory, this should ALWAYS be true.
	if (find(adj.begin(), adj.end(), a) == adj.end()){
	  //If is close enough...
	  if (euclidean(a, nodes[i]) < 1.5){
	    //Insert it in both neighbors vectors (The graph is non-directed).
	    neighbors[nodes[i]].push_back(a);
	    neighbors[a].push_back(nodes[i]);
	  }
	}
      }
    }
  }

  //This initializes things needed by Dijkstra's algorithm.
  void initialize(){
    //We need a fresh map for every graph, and since dist is a global variable we have to clean it
    dist.clear();
    //Set dist of all nodes to infinity except for the starting node.
    for (int i=0; i<nodes.size(); ++i){
      dist[nodes[i]] = infinity;
    }
    dist[point(0.0, 0.0)] = 0.00;
  }

  //maxPath is the restriction given in the problem statement (d).
  //finalPoint is where we want to get.
  void dijkstra(const double &maxPath, const point &finalPoint){

    initialize();
    
    //Used to get the point with less dist from all reachable points.
    priority_queue<point, vector<point>, heapCompare > q;
    //We always start at the origin
    q.push(point(0.0, 0.0));
    
    while (!q.empty()){
      point u = q.top();
      q.pop();
      //Do not visit a node if it's not even possible to reach it within the given constraint in straight line.
      if (euclidean(point(0.00, 0.00), u) + euclidean(u, finalPoint) <= maxPath){
	for (int i=0; i<neighbors[u].size(); ++i){
	  point v = neighbors[u][i];
	  //Relax
	  if (dist[neighbors[u][i]] > (dist[u] + euclidean(u,v))){
	    dist[neighbors[u][i]] = dist[u] + euclidean(u, v);
	    //Push reachable node into the queue.
	    q.push(v);
	  }
	}
      }
    }
  }
};



int main(){
  while (true){

    //Lame code to check if we got an '*'
    string s;
    for (s = ""; s == ""; getline(cin, s));
    if (s == "*") break;


    graph g;

    stringstream line;
    line << s;

    int w,h;
    //Read the coordinates of the final point
    line >> w >> h;

    //Insert the final and starting point
    g.insert(point((double)w, (double)h));
    g.insert(point(0.00, 0.00));

    //Quantity of points
    int noPoints;
    cin >> noPoints;
    //Read each point and insert it
    for (int i=0; i<noPuntos; ++i){
      double x,y;
      cin >> x >> y;
      g.insert(point(x,y));
    }
    
    //Read the maximum path's length.
    double maxPath;
    cin >> maxPath;

    g.dijkstra(maxPath, point((double)w, (double)h));

    if (dist[point((double)w, (double)h)] < maxPath){
      printf("I am lucky!\n");
    }else{
      printf("Boom!\n");
    }
   
  }
  return 0;
}
