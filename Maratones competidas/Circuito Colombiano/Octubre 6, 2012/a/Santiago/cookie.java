
import java.awt.geom.Area;
import java.awt.geom.Path2D;
import java.awt.geom.PathIterator;
import java.awt.geom.Rectangle2D;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;


public class cookie 
{
    static class Scanner
    {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        
        String nextLine()
        {
            String next;
            try 
            {
                next = br.readLine();
            } 
            catch (IOException ex) 
            {
                throw(new RuntimeException(ex));
            }
            return next;
        }
        
        String next()
        {
            while(st == null || !st.hasMoreTokens())
            {
                String linea = nextLine();
                if(linea == null)
                    return null;
                st = new StringTokenizer(linea);
            }
            return st.nextToken();
        }
        
        int nextInt()
        {
            return Integer.parseInt(next());
        }

        private long nextLong() {
            return Long.parseLong(next());
        }
    }
    
    static Rectangle2D readRectangle(long x0, long y0, long x1, long y1)
    {

    	long xMin = Math.min(x0, x1);
    	long yMin = Math.min(y0, y1);
    	long xMax = Math.max(x0, x1);
    	long yMax = Math.max(y0, y1);
    	return new Rectangle2D.Double(xMin, yMin, xMax - xMin, yMax - yMin);
    }
    
    public static List <Area> getAreas(Area area) 
    {
    	PathIterator iter = area.getPathIterator(null);
    	List<Area> areas = new ArrayList<Area>();
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
    		iter.next();
    	}
    	return areas;
    }
    
    public static void main(String[] args)
    {
        Scanner sc = new Scanner();
        int casos = sc.nextInt();
        for(int caso = 0; caso < casos; caso++)
        {
            Rectangle2D inicial = readRectangle(sc.nextLong(), sc.nextLong(), sc.nextLong(), sc.nextLong());
            Area area = new Area(inicial);
            if(area.isEmpty())
            	System.out.println();
            int n = sc.nextInt();
            for(int i = 0; i < n; i++)
            {
                 Rectangle2D nuevo = readRectangle(sc.nextLong(), sc.nextLong(), sc.nextLong(), sc.nextLong());
                 area.subtract(new Area(nuevo));
            }
            List <Area> areas = getAreas(area);
            for(int i = 0; i < areas.size(); i++)
            {
            	if(areas.size() != 1 && areas.get(i).equals(new Area(inicial)))
            	{
            		areas.remove(i);
            		i = -1;
            	}
            }
            outer:
            for(int i = 0; i < areas.size(); i++)
            {
            	for(int j = i + 1; j < areas.size(); j++)
            	{
            		Area aI = areas.get(i);
            		Area aJ = areas.get(j);
            		Area te = new Area(areas.get(i));
            		te.add(areas.get(j));
            		if(getAreas(te).size() == 1)
            		{
	            		areas.remove(aI);
	            		areas.remove(aJ);
	            		areas.add(te);
	            		i = -1;
	            		continue outer;
            		}
            	}
            }
            System.out.println(areas.size());
        }
    }
    
}
