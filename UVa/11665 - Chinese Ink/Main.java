// Chinese Ink

import java.util.*;
import java.awt.geom.*;

class Main {
    
    public static void main(String [] args) {
        Scanner cin = new Scanner(System.in);
        while (true) {
            int n = cin.nextInt();
            if (n == 0) break;
            cin.nextLine();
            (new Solver(n, cin)).run();
        }
    }
}

class Solver {
    ArrayList<ArrayList<Point2D>> polygons;
    ArrayList<Area> areas;
    int[] parent;
    int n;
    
    Solver(int n, Scanner cin) {
        this.n = n;
        polygons = new ArrayList<ArrayList<Point2D>>();
        areas = new ArrayList<Area>();
        parent = new int[n];

        for (int k = 0; k < n; ++k) {
            String[] tokens = cin.nextLine().split("\\s+");
            
            ArrayList< Point2D > poly = new ArrayList<Point2D>();
            for (int p = 0; p < tokens.length; p += 2){
                poly.add( new Point2D.Double(Integer.valueOf(tokens[p]), Integer.valueOf(tokens[p + 1]))  );
            }
            
            Path2D.Double path = new Path2D.Double();
            path.moveTo(poly.get(0).getX(), poly.get(0).getY());
            for (int i = 1; i < poly.size(); i++) path.lineTo(poly.get(i).getX(), poly.get(i).getY());
            path.closePath();
            areas.add(new Area(path));
            polygons.add(poly);
        }
    }
    
    boolean intersect(int i, int j) {
        ArrayList<Point2D> pi = polygons.get(i), pj = polygons.get(j);
        for (int ii = 0; ii < pi.size(); ++ii) {
            for (int jj = 0; jj < pj.size(); ++jj) {
                
                int iii = (ii + 1) % pi.size();
                int jjj = (jj + 1) % pj.size();
                
                if (Line2D.linesIntersect(pi.get(ii).getX(), pi.get(ii).getY(),
                                          pi.get(iii).getX(), pi.get(iii).getY(),
                                          
                                          pj.get(jj).getX(), pj.get(jj).getY(),
                                          pj.get(jjj).getX(), pj.get(jjj).getY() ) ) {
                                              return true;
                }
            }
        }
        
        Area intersection = new Area(areas.get(i));
        intersection.intersect(areas.get(j));
        return !intersection.isEmpty();
    }
    
    
    int find(int i){
        if (parent[i] == i) return i;
        int ans = find(parent[i]);
        parent[i] = ans;
        return ans;
    }
    
    void join(int i, int j) {
        int pi = find(i);
        int pj = find(j);
        if (pi != pj) parent[pi] = pj;
    }
    
    void run() {
        for (int i = 0; i < n; ++i) parent[i] = i;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (intersect(i, j)) join(i, j);
            }
        }
        TreeSet<Integer> set = new TreeSet<Integer>();
        for (int i = 0; i < n; ++i) set.add(find(i));
        System.out.println(set.size());
    }
}