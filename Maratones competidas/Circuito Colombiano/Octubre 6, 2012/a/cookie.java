// Just experimenting. This gives WA.
import java.util.*;
import java.awt.*;
import java.awt.geom.*;
import java.io.*;

class cookie {
    
    public static Rectangle buildRectangle(long x1, long y1, long x2, long y2) {
        if (x2 < x1) {
            long t = x1;
            x1 = x2;
            x2 = t;
        }
        
        if (y2 < y1) {
            long t = y1;
            y1 = y2;
            y2 = t;
        }
        assert x1 <= x2;
        assert y1 <= y2;
        
        Rectangle ans = new Rectangle(0, 0, -1, -1);
        ans.add((int)x1, (int)y1);
        ans.add((int)x2, (int)y2);
        return ans;
    }
    
    static int countDisjointsPolygonsInArea(Area area) {
        int ans = 0;
        PathIterator iter = area.getPathIterator(null);
        ArrayList<Point2D.Double> points = new ArrayList<Point2D.Double>();
        while (!iter.isDone()) {
              double[] buffer = new double[6];
              switch (iter.currentSegment(buffer)) {
              case PathIterator.SEG_MOVETO:
              case PathIterator.SEG_LINETO:
                  points.add(new Point2D.Double(buffer[0], buffer[1]));
                  break;
              case PathIterator.SEG_CLOSE:
                  ans++;
                  // Here, points contains one of the polygons
                  points.clear();
                  break;
              }
              iter.next();
          }
          return ans;
    }
    
    public static void printArea(Area area) {
        PathIterator iter = area.getPathIterator(null);
        while(!iter.isDone()) 
        {
            double point[] = new double[6];
            int type = iter.currentSegment(point); 
            if (type == PathIterator.SEG_MOVETO) {
                System.out.print("move to");
            } else if (type == PathIterator.SEG_LINETO) {
                System.out.print("line to");
            } else if (type == PathIterator.SEG_CLOSE) {
                System.out.print("close");
            }            
            System.out.printf(" (%f, %f)\n", point[0], point[1]);
            iter.next();
        }
    }
    
    
    public static ArrayList <Area> getAreas(Area area) 
    {
        PathIterator iter = area.getPathIterator(null);
        ArrayList<Area> areas = new ArrayList<Area>();
        Path2D.Double poly = new Path2D.Double();
        while(!iter.isDone()) 
        {
            double point[] = new double[2];
            int type = iter.currentSegment(point); 
            if(type == PathIterator.SEG_MOVETO)
                poly.moveTo(point[0], point[1]);
            else if(type == PathIterator.SEG_CLOSE) 
            {
                areas.add(new Area(poly));
                poly.reset();
            }
            else
                poly.lineTo(point[0], point[1]);
                
                
                
            
                if (type == PathIterator.SEG_MOVETO) {
                    System.out.print("move to");
                } else if (type == PathIterator.SEG_LINETO) {
                    System.out.print("line to");
                } else if (type == PathIterator.SEG_CLOSE) {
                    System.out.print("close");
                }
                
                System.out.printf(" (%f, %f)\n", point[0], point[1]);
                
            
            
            iter.next();
        }
        return areas;
    }
        
    public static void main(String [] args) {
        Scanner cin = new Scanner(System.in);
        PrintStream cout = System.out;
        

        for (int runs = cin.nextInt(); runs > 0; --runs) {
            Area cookie = new Area(buildRectangle(cin.nextLong(), cin.nextLong(), cin.nextLong(), cin.nextLong()));
            int n = cin.nextInt();
            for (int i = 0; i < n; ++i) {
                Rectangle chip = buildRectangle(cin.nextLong(), cin.nextLong(), cin.nextLong(), cin.nextLong());
                cookie.subtract(new Area(chip));
            }
//            cout.println(countDisjointsPolygonsInArea(cookie));
            cout.println(getAreas(cookie).size());
        }
        cout.println();
    }
}