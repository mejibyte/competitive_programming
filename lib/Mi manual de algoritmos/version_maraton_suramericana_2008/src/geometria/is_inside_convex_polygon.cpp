/*
  Returns true if point a is inside convex polygon p.
  Note that if point a lies on the border of p it
  is considered outside.

  We assume p is convex! The result is useless if p
  is concave.
 */
bool insideConvexPolygon(const vector<point> &p, const point &a){
  int mask = 0;
  int n = p.size();
  for (int i=0; i<n; ++i){
    int j = (i+1)%n;
    double z = turn(p[i], p[j], a);
    if (z < 0.0){
      mask |= 1;
    }else if (z > 0.0){
      mask |= 2;
    }else if (z == 0.0) return false;
    if (mask == 3) return false;
  }
  return mask != 0;

}
