#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Point{
  int x, y;
  bool operator < (const Point &p) const {
    return (x < p.x || (x == p.x && y < p.y));
  }
};

// 2D cross product.
// Return a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.
int cross(const Point &O, const Point &A, const Point &B)
{
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is the same as the first one.
vector<Point> convexHull(vector<Point> P)
{
	int n = P.size(), k = 0;
	vector<Point> H(2*n);
 
	// Sort Points lexicographically
	sort(P.begin(), P.end());
 
	// Build lower hull
	for (int i = 0; i < n; i++) {
		while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}
 
	// Build upper hull
	for (int i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}
 
	H.resize(k);
	return H;
}

void printPnt(const Point &p){
  cout << "(" << p.x << "," << p.y << ")";
}

int main(){
  int n;
  cin >> n;
  while (n){
    //procesar caso
    vector<Point> g(n);
    for (int i=0; i<n; ++i){
      int x, y;
      cin >> x >> y;
      g[i].x = x;
      g[i].y = y;
    }
    /*cout << "g.size() es: " << g.size() << endl;
    for (int i=0; i<n; ++i){
      printPnt(g[i]);
      cout << " ";
    }
    cout << endl; */
    vector<Point> chull = convexHull(g);
    /*cout << "chull.size() es: " << chull.size() << endl;
    for (int i=0; i<chull.size(); ++i){
      printPnt(chull[i]);
      cout << " ";
    }
    cout << endl;*/
    chull.pop_back();
    if (chull.size() == n){
      cout << "No\n";
    }else{
      cout << "Yes\n";
    }
    cin >> n;
  }
  return 0;
}
