//Point
//Choose one of these two:
struct P {
  double x, y; P(){}; P(double q, double w) : x(q), y(w){}
};
struct P {
  int x, y; P(){}; P(int q, int w) : x(q), y(w){}
};

// Polar angle
// Returns an angle in the range [0, 2*Pi) of a given Cartesian point.
// If the point is (0,0), -1.0 is returned.
// REQUIRES:
// include math.h
// define EPS 0.000000001, or your choice
// P has members x and y.
double polarAngle( P p )
{
  if(fabs(p.x) <= EPS && fabs(p.y) <= EPS) return -1.0;
  if(fabs(p.x) <= EPS) return (p.y > EPS ? 1.0 : 3.0) * acos(0);
  double theta = atan(1.0 * p.y / p.x);
  if(p.x > EPS) return(p.y >= -EPS ? theta : (4*acos(0) + theta));
  return(2 * acos( 0 ) + theta);
}

//Point inside polygon
// Returns true iff p is inside poly.
// PRE: The vertices of poly are ordered (either clockwise or
//      counter-clockwise.
// POST: Modify code inside to handle the special case of "on
// an edge".
// REQUIRES:
// polarAngle()
// include math.h
// include vector
// define EPS 0.000000001, or your choice
bool pointInPoly( P p, vector< P > &poly )
{
  int n = poly.size();
  double ang = 0.0;
  for(int i = n - 1, j = 0; j < n; i = j++){
    P v( poly[i].x - p.x, poly[i].y - p.y );
    P w( poly[j].x - p.x, poly[j].y - p.y );
    double va = polarAngle(v);
    double wa = polarAngle(w);
    double xx = wa - va;
    if(va < -0.5 || wa < -0.5 || fabs(fabs(xx)-2*acos(0)) < EPS){
        // POINT IS ON THE EDGE
        assert( false );
        ang += 2 * acos( 0 );
        continue;
      }
    if( xx < -2 * acos( 0 ) ) ang += xx + 4 * acos( 0 );
    else if( xx > 2 * acos( 0 ) ) ang += xx - 4 * acos( 0 );
    else ang += xx;
  }
  return( ang * ang > 1.0 );
}
