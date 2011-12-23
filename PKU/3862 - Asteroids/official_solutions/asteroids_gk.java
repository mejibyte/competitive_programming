import java.util.*;
import java.io.*;

class asteroids_gk {
	static Scanner in;
	static PrintWriter out;
	static final double EPS = 1e-10;
	static Point magic = new Point(Math.E, Math.PI, Math.E * Math.PI);
	
	static class Point {
		double x, y, z;
		Point(double x, double y, double z) { this.x = x; this.y = y; this.z = z; }
		Point plus(Point p) { return new Point(x + p.x, y + p.y, z + p.z); }
		Point minus(Point p) { return new Point(x - p.x, y - p.y, z - p.z); }
		double dot(Point p) { return x * p.x + y * p.y + z * p.z; }
		Point cross(Point p) { return new Point(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x );}
		double norm() { return Math.sqrt(dot(this)); }
		Point scale(double a) { return new Point(x * a, y * a, z * a); }
		double normM() { return dot(this) * Math.signum(dot(magic)); }

		double angle(final Point c, final Point base) {
			Point p = minus(c);
			return Math.atan2(p.cross(base).normM(), p.dot(base));
		}
	}
	
	static class Averager {
		Point p = new Point(0, 0, 0);
		double w = 0;
		
		void add(Point dp, double dw) {
			p = p.plus(dp.scale(dw));
			w += dw;
		}
		
		Point get(double a) {
			return p.scale(a / w);
		}
	}

	List<Point> on(Point[] points, int i, int j, int k) {
		Point normal = normal(points[j], points[i], points[k]);
		double d = normal.dot(points[i]);
		boolean neg = false;
		boolean pos = false;
		List<Point> on = new ArrayList<Point>();
		for (int q = 0; q < points.length; q++) {
			double dist = normal.dot(points[q]) - d;
			if (Math.abs(dist) < EPS) {
				on.add(points[q]);
			} else if ((neg |= dist < 0) & (pos |= dist > 0)) {
				return null;
			}
		}
		return on;
	}

	Point normal(Point p1, Point p2, Point p3) {
		return p1.minus(p2).cross(p3.minus(p2));
	}

	double calcDist() {
		int n = in.nextInt();
		
		Point[] points = new Point[n];
		for (int i = 0; i < n; i++) {
			points[i] = new Point(in.nextInt(), in.nextInt(), in.nextInt());
		}

		List<List<Point>> faces = new ArrayList<List<Point>>();
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				for (int k = j + 1; k < n; k++) {
					List<Point> on = on(points, i, j, k);
					if (on != null && on.get(2) == points[k]) {
						faces.add(on);
					}
				}
			}
		}
		
		Point first = points[0];
		Averager mma = new Averager();
		for (List<Point> face : faces) {
			Averager ca = new Averager();
			for (Point p : face) {
				ca.add(p, 1);
			}
			final Point c = ca.get(1);
			final Point base = face.get(0).minus(c);
			Collections.sort(face, new Comparator<Point>() {
				@Override
				public int compare(Point p1, Point p2) {
					return Double.compare(p1.angle(c, base), p2.angle(c, base));
				}
			});
			
			
			int f = face.size();
			Averager ma = new Averager();
			for (int q = 0; q < f; q++) {
				Point p1 = face.get(q).minus(c);
				Point p2 = face.get((q + f - 1) % f).minus(c);
				ma.add(p1.plus(p2), p1.cross(p2).norm());
			}
			
			Point mc = ma.get(1.0 / 3).plus(c).minus(first);
			Point normal = normal(face.get(0), face.get(1), face.get(2));
			mma.add(mc, Math.abs(ma.w * normal.dot(mc)) / normal.norm());
		}
		Point mmc = mma.get(3.0 / 4).plus(first);
		
		double min = Double.MAX_VALUE;
		for (List<Point> face : faces) {
			Point normal = normal(face.get(0), face.get(1), face.get(2));
			min = Math.min(min, Math.abs(normal.dot(mmc) - normal.dot(face.get(0))) / normal.norm());
		}
		return min;
	}

	void run() throws IOException {
		out.println(calcDist() + calcDist());
	}

	public static void main(String[] args) throws Exception {        
		in = new Scanner(System.in);
		out = new PrintWriter(System.out);

		new asteroids_gk().run();

		in.close();
		out.close();
	}
}
