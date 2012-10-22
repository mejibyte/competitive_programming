// Doors and Penguins solution by S Zeil
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;


struct Coord {
  int x;
  int y;
  bool isDoors;

  Coord() {}
  Coord (int xx, int yy, bool doors)
    : x(xx), y(yy), isDoors(doors)
    {}

};

ostream& operator<< (ostream& out, const Coord& c)
{
  out << "(" << c.x << "," << c.y << "," << c.isDoors << ")";
  return out;
}

int evalLine (const Coord& p1, const Coord& p2, const Coord& c)
  // Evaluate c on the line passing through p1 and p2, returning
  // 0 if c lies on the line, 1 if it lies "above" the line, -1 if
  // it lies "below" it.
{
  int z = (p2.x - p1.x) * (c.y - p1.y) - (p2.y - p1.y) * (c.x - p1.x);
  
  return (z > 0) ? 1 : ((z == 0)? 0 : -1);
}




int main (int argc, char** argv)
{
  //ifstream in ("doors.in");
  istream& in = cin;

  //ofstream out ("doors.out");
  ostream& out = cout;


  int caseNum = 0;

  int D, P;

  in >> D >> P;

  while (D > 0 || P > 0)
    {

      ++caseNum;

      // The "rectangular" nature of the tables is something of a red herring.
      // A solution exists if you can find a line that divides the points
      // representing the 4 corners of each doors vendor from the points
      // representing the 4 corners of each pengins vendor.

      Coord* doors = new Coord[4*D];
      Coord* penguins = new Coord[4*P];
      
      Coord* all = new Coord[4*D + 4*P];
      int k = 0;

      for (int i = 0; i < D; ++i) 
	{
	  int x1, y1, x2, y2;
	  in >> x1 >> y1 >> x2 >> y2;
	  
	  doors[4*i] = all[k] = Coord(x1, y1, true);
	  ++k;
	  doors[4*i+1] = all[k] = Coord(x2, y2, true);
	  ++k;
	  doors[4*i+2] = all[k] = Coord(x1, y2, true);
	  ++k;
	  doors[4*i+3] = all[k] = Coord(x2, y1, true);
	  ++k;
	}

      for (int i = 0; i < P; ++i) 
	{
	  int x1, y1, x2, y2;
	  in >> x1 >> y1 >> x2 >> y2;
	  
	  penguins[4*i] = all[k] = Coord(x1, y1, false);
	  ++k;
	  penguins[4*i+1] = all[k] = Coord(x2, y2, false);
	  ++k;
	  penguins[4*i+2] = all[k] = Coord(x1, y2, false);
	  ++k;
	  penguins[4*i+3] = all[k] = Coord(x2, y1, false);
	  ++k;
	}


      // It's possible to solve this by finding the convex hull of the
      // two sets and then checking to see if the hulls intersect.
      // Or, find the convex hull of one set of points and see if any
      // point in the other set is inside that hull.  If the hull is found
      // by the O(n log n) divide and conquer, these will be O(n^2 log n).
      // If the more general gift-wrapping algorithm is used, they would 
      // be O(n^3). That would be an O(n^2) approach.

      // This is a much easier-to-program approach that is  O(n^3)
      // but still reasonably fast in practice.
      // It's based on the idea that, if a dividing line exists, it could 
      // be rotated slightly until it touches exactly one door point 
      // and one penguin point. Consequently, if we consider each 
      // possible pair of one door and one penguin point, we can check to
      // see if the line passing through those two points paritions the
      // remaining points (without touching any of them).

      bool found = false;

      for (int i = 0; (i < 4*D) && !found; ++i) 
	{
	  //	  if (i % 10 == 0)
	  //	    cerr << "i: " << i << endl;
	  for (int j = 0; (j < 4*P) && !found; ++j) 
	    {
	      //
	      // Consider the line passing through doors[i] and penguins[j]
	      //
	      /*
		cerr << "i " << i << " " << doors[i]
		   << " j " << j << " " << penguins[j] << endl;
	      */
	      bool failed = false;
	      int dState = 0;
	      int numOnLine = 0;
	      for (int k = 0; (k < 4*D + 4*P) && !failed; ++k)
		{
		  int state = evalLine(doors[i], penguins[j], all[k]);
		  if (state == 0)
		    {
		      // point lies on the line
		      ++numOnLine;
		      failed = (numOnLine > 2);
		      /*
			cerr << "numOnLine " << numOnLine << endl;
			if (failed)
			  cerr << "collinear failure " << i << " " << j << " " << k << endl;
		      */
		    }
		  else if (dState == 0)
		    {
		      // This is the first point off the line we have seen
		      // From it we learn which side of the line the doors 
		      // points should all lie.
		      dState =  (all[k].isDoors) ? state : -state;
		    }
		  else
		    {
		      // Point is off the line. If it's on the "wrong" side,
		      // then this is not a dividing line
		      if (all[k].isDoors)
			failed = (state != dState);
		      else
			failed = (state == dState);
		      /*
		       if (failed)
		        {
		         cerr << "state failure " << i << ":" << doors[i]
		             << " / " << j << ":" << penguins[j]
		             << " at " << k << ":" << all[k] << endl;
		        }
		      */
		      // As a speed optimization for large data sets,
		      // swap the point on which we failed to the front
		      // of the set so we will try that one earlier from now
		      // on.
		      if (failed)
			{
			  swap (all[k], all[0]);
			  // if (i % 10 == 0 && j == 0)
			  //   cerr << "Failed at " << k << endl;
			}
		    }
		  }
	      dState = -dState;
	      for (int k = 0; k < 4*P && !failed; ++k)
		if (k != j)
		  {
		    int state = evalLine(doors[i], penguins[j], penguins[k]);
		    if (state == 0)
		      failed = true;
		    else if (state != dState)
		      failed = true;
		  }
	      if (!failed) {
		found = true;
	      }
	    }
	}
      
      if (caseNum > 1)
	out << endl;

      out << "Case " << caseNum << ": ";

      if (found)
	out << "It is possible to separate the two groups of vendors." << endl;
      else
	out << "It is not possible to separate the two groups of vendors." << endl;

      delete [] doors;
      delete [] penguins;
      delete [] all;

      in >> D >> P;

    }

  return 0;
}
