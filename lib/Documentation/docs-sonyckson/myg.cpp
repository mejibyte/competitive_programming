// Implementation of Monotone Chain Convex Hull algorithm.
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
#define ll long long
struct point {
	int x, y;
	point(){}
	point(int a, int b){ x = a;y = b;}
	bool operator <(const point &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};

// 2D cross product.
// Return a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.
int cross(const point &O, const point &A, const point &B)
{
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is the same as the first one.
vector<point> convexHull(vector<point> P)
{
	int n = P.size(), k = 0;
	vector<point> H(2*n);
	// Sort points lexicographically
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
/////////////////////////      hiiiiper rapida :)
int TAM;
point H[1500];
void convexHull(point P[], int n)
{
	int k = 0;
	// Sort points lexicographically
	sort(P, P+n);
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
	TAM = k;
}
