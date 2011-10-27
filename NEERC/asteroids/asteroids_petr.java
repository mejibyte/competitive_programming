import java.io.BufferedReader;
import java.io.FileReader;
import java.io.PrintWriter;
import java.io.IOException;
import java.util.*;

public class asteroids_petr implements Runnable {
    static final int MAX_POWER = 3;

    static class Point {
        double x;
        double y;
        double z;

        Point(double x, double y, double z) {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        void swapXY() {
            double t = x;
            x = y;
            y = t;
        }

        void swapXZ() {
            double t = x;
            x = z;
            z = t;
        }

        public void rotateXY(double v) {
            double nx = x * Math.cos(v) - y * Math.sin(v);
            double ny = x * Math.sin(v) + y * Math.cos(v);
            x = nx;
            y = ny;
        }
    }

    static class Point2D implements Comparable<Point2D> {
        double x;
        double y;
        double angle;

        Point2D(double x, double y) {
            this.x = x;
            this.y = y;
        }

        public int compareTo(Point2D point2D) {
            return Double.compare(angle, point2D.angle);
        }
    }

    static int count = 0;

    static class Plane {
        double a;
        double b;
        double c;
        double d;

        public Plane(Point p1, Point p2, Point p3) {
            a = (p2.z - p1.z) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.z - p1.z);
            b = (p2.x - p1.x) * (p3.z - p1.z) - (p2.z - p1.z) * (p3.x - p1.x);
            c = (p2.y - p1.y) * (p3.x - p1.x) - (p2.x - p1.x) * (p3.y - p1.y);
            double z = Math.sqrt(a * a + b * b + c * c);
            a /= z;
            b /= z;
            c /= z;
            d = -(a * p1.x + b * p1.y + c * p1.z);
        }

        public int side(Point p) {
            double z = sideDouble(p);
            if (Math.abs(z) < 1e-11)
                return 0;
            else if (z < 0)
                return -1;
            else
                return 1;
        }

        public double sideDouble(Point p) {
            return a * p.x + b * p.y + c * p.z + d;
        }
    }

    static class Polyhedron {
        Point[] points;

        void swapXY() {
            for (Point p : points)
                p.swapXY();
        }

        void swapXZ() {
            for (Point p : points)
                p.swapXZ();
        }

        double integrate(double[] what) {
            Set<Double> allXs = new TreeSet<Double>();
            for (Point p : points)
                allXs.add(p.x);
            Double prev = null;
            double sum = 0;
            for (Double cur : allXs) {
                if (prev != null) {
                    double[] areas = new double[MAX_POWER + 1];
                    double[] xs = new double[MAX_POWER + 1];
                    for (int i = 0 ; i <= MAX_POWER; ++i) {
                        xs[i] = (prev * (MAX_POWER - i) + cur * i) / MAX_POWER;
                        areas[i] = getArea(xs[i]) * evalPolynomial(what, xs[i]);
                    }
                    sum += (cur - prev) / 8.0 * (areas[0] + 3 * areas[1] + 3 * areas[2] + areas[3]);
                }
                prev = cur;
            }
            return sum;
        }

        private double evalPolynomial(double[] koef, double x) {
            double res = 0;
            for (int i = koef.length - 1; i >= 0; --i)
                res = res * x + koef[i];
            return res;
        }

        static Random random = new Random();

        private double getArea(double x) {
            List<Point2D> p2d = new ArrayList<Point2D>();
            for (Point p1 : points) {
                if (p1.x == x) {
                    p2d.add(new Point2D(p1.y, p1.z));
                    continue;
                }
                if (p1.x < x)
                    for (Point p2 : points) {
                        if (p2.x == x) {
                            continue;
                        }
                        if (p2.x > x) {
                            p2d.add(new Point2D(p1.y + (p2.y - p1.y) * (x - p1.x) / (p2.x - p1.x), p1.z + (p2.z - p1.z) * (x - p1.x) / (p2.x - p1.x)));
                        }
                    }
            }
            if (p2d.isEmpty())
                return 0.0;
            Point2D corner = new Point2D(0, 0);
            double totalWeight = 0.0;
            for (Point2D p : p2d) {
                double weight = random.nextDouble();
                corner.x += weight * p.x;
                corner.y += weight * p.y;
                totalWeight += weight;
            }
            double dx = -corner.x / totalWeight;
            double dy = -corner.y / totalWeight;
            for (Point2D p : p2d) {
                p.x += dx;
                p.y += dy;
                p.angle = Math.atan2(p.y, p.x);
            }
            Collections.sort(p2d);
            corner = p2d.get(0);
            for (Point2D p : p2d) {
                if (p.x < corner.x || p.x == corner.x && p.y < corner.y)
                    corner = p;
            }
            int start =0;
            for (int i = 0; i < p2d.size(); ++i)
                if (p2d.get(i) == corner)
                    start = i;
            List<Point2D> hull = new ArrayList<Point2D>();
            for (int i = 0; i <= p2d.size(); ++i) {
                hull.add(p2d.get((start + i) % p2d.size()));
                while (hull.size() >= 3) {
                    Point2D a = hull.get(hull.size() - 3);
                    Point2D b = hull.get(hull.size() - 2);
                    Point2D c = hull.get(hull.size() - 1);
                    /*if ((b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x) == 0 && (b.x - a.x) * (c.x - b.x) + (b.y - a.y) * (c.y - b.y) < 0)
                        throw new RuntimeException();*/                    
                    if ((b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x) <= 0)
                        hull.remove(hull.size() - 2);
                    else
                        break;
                }
            }
            double area = 0;
            for (int i = 0; i < hull.size() - 1; ++i) {
                Point2D a = hull.get(i);
                Point2D b = hull.get(i + 1);
                area += (a.y + b.y) * (a.x - b.x);
                if (i < hull.size() - 2) {
                    Point2D c = hull.get(i + 2);
                    if ((b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x) <= 0)
                        throw new RuntimeException();
                }
            }
            if (area < -1e-12)
                throw new RuntimeException();
            return area / 2.0;
        }

        public double getDistance(Point center) {
            double res = Double.MAX_VALUE;
            for (int i1 = 0; i1 < points.length; ++i1)
                for (int i2 = i1 + 1; i2 < points.length; ++i2)
                    for (int i3 = i2 + 1; i3 < points.length; ++i3) {
                        Plane plane = new Plane(points[i1], points[i2], points[i3]);
                        boolean[] was = new boolean[3];
                        for (Point p : points)
                            was[plane.side(p) + 1] = true;
                        if (was[0] && was[2])
                            continue;
                        res = Math.min(res, Math.abs(plane.sideDouble(center)));
                    }
            return res;
        }

        public void rotateXY(double v) {
            for (Point p : points)
                p.rotateXY(v);
        }
    }

    Polyhedron parsePolyhedron() throws IOException {
        int n = nextInt();
        Polyhedron p = new Polyhedron();
        p.points = new Point[n];
        for (int i = 0; i < n; ++i) {
            int x = nextInt();
            int y = nextInt();
            int z = nextInt();
            p.points[i] = new Point(x, y, z);
        }
        return p;
    }

    private void solve() throws IOException {
        Polyhedron[] polyhedrons = new Polyhedron[2];
        for (int i = 0; i < 2; ++i) {
            polyhedrons[i] = parsePolyhedron();
            /*polyhedrons[i].rotateXY(0.54326);
            polyhedrons[i].swapXZ();
            polyhedrons[i].rotateXY(0.1324543);
            polyhedrons[i].swapXZ();
            polyhedrons[i].rotateXY(0.5416512);*/
        }
        double res = 0.0;
        for (Polyhedron polyhedron : polyhedrons) {
            double volume = polyhedron.integrate(new double[]{1});
            double xc = polyhedron.integrate(new double[]{0, 1}) / volume;
            polyhedron.swapXY();
            double yc = polyhedron.integrate(new double[]{0, 1}) / volume;
            polyhedron.swapXY();
            polyhedron.swapXZ();
            double zc = polyhedron.integrate(new double[]{0, 1}) / volume;
            polyhedron.swapXZ();
            System.out.println("Center of mass: (" + xc + ", " + yc + ", " + zc + ")");
            res += polyhedron.getDistance(new Point(xc, yc, zc));
        }
        writer.println(res);
    }


    public static void main(String[] args) throws InterruptedException {
        Thread thread = new Thread(new asteroids_petr());
        thread.start();
        thread.join();
        System.err.println(count);
    }

    static final String TASK_ID = "asteroids";
    static final String IN_FILE = TASK_ID + ".in";
    static final String OUT_FILE = TASK_ID + ".out";
    BufferedReader reader;
    StringTokenizer tokenizer;
    PrintWriter writer;

    public void run() {
        try {
            reader = new BufferedReader(new FileReader(IN_FILE));
            tokenizer = null;
            writer = new PrintWriter(OUT_FILE);
            solve();
            reader.close();
            writer.close();
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    long nextLong() throws IOException {
        return Long.parseLong(nextToken());
    }

    double nextDouble() throws IOException {
        return Double.parseDouble(nextToken());
    }

    String nextToken() throws IOException {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            tokenizer = new StringTokenizer(reader.readLine());
        }
        return tokenizer.nextToken();
    }
}
