/*
  Returns the cross product of the segment that goes from
  (x1, y1) to (x3, y3) with the segment that goes from
  (x1, y1) to (x2, y2)
*/
int direction(int x1, int y1, int x2, int y2, int x3, int y3) {
    return (x3 - x1) * (y2 - y1) - (y3 - y1) * (x2 - x1);
}

/*
  Finds the intersection between two segments (Not infinite
  lines!)
  Segment 1 goes from point (x0, y0) to (x1, y1).
  Segment 2 goes from point (x2, y2) to (x3, y3).

  (Can be modified to find the intersection between a segment
  and a line)

  Handles the case when the 2 segments are:
  *Parallel but don't lie on the same line (No intersection)
  *Parallel and both lie on the same line (Infinite
  *intersections or no intersections)
  *Not parallel (One intersection or no intersections)

  Returns true if the segments do intersect in any case.
*/
bool segment_segment_intersection(int x1, int y1,
                                  int x2, int y2,
                                  
                                  int x3, int y3,
                                  int x4, int y4){
                                      
    int d1 = direction(x3, y3,   x4, y4,   x1, y1);
    int d2 = direction(x3, y3,   x4, y4,   x2, y2);
    int d3 = direction(x1, y1,   x2, y2,   x3, y3);
    int d4 = direction(x1, y1,   x2, y2,   x4, y4);
    bool b1 = d1 > 0 and d2 < 0 or d1 < 0 and d2 > 0;
    bool b2 = d3 > 0 and d4 < 0 or d3 < 0 and d4 > 0;
    if (b1 and b2) return true;
    if (d1 == 0 and point_in_box(x1, y1,     x3, y3, x4, y4))
        return true;

    if (d2 == 0 and point_in_box(x2, y2,     x3, y3, x4, y4))
        return true;

    if (d3 == 0 and point_in_box(x3, y3,     x1, y1, x2, y2))
        return true;

    if (d4 == 0 and point_in_box(x4, y4,     x1, y1, x2, y2))
        return true;

    return false;
}