
#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

struct Point{
  long long x, y;
  bool operator < (const Point &p) const {
    return (x < p.x || (x == p.x &&y < p.y));
  }
};

// 2D cross product.
// Return a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.
long long cross(const Point &O, const Point &A, const Point &B)
{
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is the same as the first one.
vector<Point> convexHull(vector<Point> P)
{
	long long n = P.size(), k = 0;
	vector<Point> H(2*n);
 
	// Sort Points lexicographically
	sort(P.begin(), P.end());
 
	// Build lower hull
	for (long long i = 0; i < n; i++) {
		while (k >= 2 && cross(H[k-2], H[k-1], P[i]) < 0) k--;
		H[k++] = P[i];
	}
 
	// Build upper hull
	for (long long i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && cross(H[k-2], H[k-1], P[i]) < 0) k--;
		H[k++] = P[i];
	}
 
	H.resize(k);
	return H;
}

void printPnt(const Point &p){
  cout << "(" << p.x << "," << p.y << ")";
}

int main(){
  long long n;
  cin >> n;
  while (n--){
    //procesar caso
    long long ilen, nails;
    cin >> ilen >> nails;
    vector<Point> g(nails);
    
    for (long long i=0; i<nails; ++i){
      long long x, y;
      cin >> x >> y;
      g[i].x = x;
      g[i].y = y;
    }
    
    vector<Point> chull = convexHull(g);
    /*for (int i=0; i<chull.size(); i++){
      printPnt(chull[i]); cout << " ";
    }
    cout << endl;*/
    if (chull.size() > 1){
      long double dlen = (long double)ilen;
      long double dist = 0.0;
      for (int i=0; i<chull.size()-1; i++){
	//Euclidean distance
	//cout << "dist "<<i<<" es: " << dist <<endl;
	dist += (long double)sqrt((chull[i].x-chull[i+1].x)*(chull[i].x-chull[i+1].x)+(chull[i].y-chull[i+1].y)*(chull[i].y-chull[i+1].y));
      }
      //cout << "dist es: " << dist << endl;
      if (dlen > dist){
	cout << ilen << ".00000\n";
      }else{
	printf("%.5Lf\n", dist);
      }

    }else{ //solo hay un clavo
      cout << ilen << ".00000\n";
    }
  }
  return 0;
}
