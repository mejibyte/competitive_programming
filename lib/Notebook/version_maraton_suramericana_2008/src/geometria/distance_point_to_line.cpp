/*
  Returns the closest distance between point pnt and the line that passes through points a and b
  Idea by: http://local.wasp.uwa.edu.au/~pbourke/geometry/pointline/
 */
double distance_point_to_line(const point &a, const point &b, const point &pnt){
  double u = ((pnt.x - a.x)*(b.x - a.x) + (pnt.y - a.y)*(b.y - a.y)) / distsqr(a, b);
  point intersection;
  intersection.x = a.x + u*(b.x - a.x);
  intersection.y = a.y + u*(b.y - a.y);
  return dist(pnt, intersection);
}
