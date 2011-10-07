/*
  Returns positive if a-b-c makes a left turn.
  Returns negative if a-b-c makes a right turn.
  Returns 0.0 if a-b-c are colineal.
 */
double turn(const point &a, const point &b, const point &c){
  double z = (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
  if (fabs(z) < 1e-9) return 0.0;
  return z;
}

/*
  Returns true if polygon p is convex.
  False if it's concave or it can't be determined
  (For example, if all points are colineal we can't 
  make a choice).
 */
bool isConvexPolygon(const vector<point> &p){
  int mask = 0;
  int n = p.size();
  for (int i=0; i<n; ++i){
    int j=(i+1)%n;
    int k=(i+2)%n;
    double z = turn(p[i], p[j], p[k]);
    if (z < 0.0){
      mask |= 1;
    }else if (z > 0.0){
      mask |= 2;
    }
    if (mask == 3) return false;
  }
  return mask != 0;
}
