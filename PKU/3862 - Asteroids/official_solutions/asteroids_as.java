import java.io.*;
import java.util.*;
import static java.lang.Math.*;

public class asteroids_as implements Runnable {

    final double EPS = 1e-9;

    class Plane {
        long a, b, c, d;
        double norm;

        Plane(long a, long b, long c, long d) {
            this.a = a;
            this.b = b;
            this.c = c;
            this.d = d;
            norm = sqrt(a * a + b * b + c * c);
        }
    }

    class Point2D implements Comparable<Point2D> {
        double x;
        double y;
        double ang;

        Point2D(double x, double y) {
            this.x = x;
            this.y = y;
            if (x == 0 && y == 0) {
                ang = Double.NEGATIVE_INFINITY;
            } else {
                ang = atan2(y, x);
            }
        }

        public int compareTo(Point2D o) {
            return ang < o.ang ? -1 : ang > o.ang ? 1 : 0;
        }

        @Override
        public String toString() {
            return "(" + x + "," + y + ")";
        }
    }

    class Polyhedron {
        int n;
        int[] x;
        int[] y;
        int[] z;

        Polyhedron(Scanner in) {
            n = in.nextInt();
            assert 4 <= n && n <= 60;
            x = new int[n];
            y = new int[n];
            z = new int[n];
            for (int i = 0; i < n; i++) {
                x[i] = in.nextInt();
                y[i] = in.nextInt();
                z[i] = in.nextInt();
            }
        }

        double dist() {
            int minx = x[0];
            int miny = y[0];
            int minz = z[0];
            for (int i = 1; i < n; i++) {
                if (x[i] < minx || x[i] == minx && y[i] < miny || x[i] == minx && y[i] == miny && z[i] < minz) {
                    minx = x[i];
                    miny = y[i];
                    minz = z[i];
                }
            }

            ArrayList<Plane> faces = new ArrayList<Plane>();

            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    for (int k = j + 1; k < n; k++) {
                        long a = (y[j] - y[i]) * (z[k] - z[i]) - (y[k] - y[i]) * (z[j] - z[i]);
                        long b = (z[j] - z[i]) * (x[k] - x[i]) - (z[k] - z[i]) * (x[j] - x[i]);
                        long c = (x[j] - x[i]) * (y[k] - y[i]) - (x[k] - x[i]) * (y[j] - y[i]);
                        long d = -(a * x[i] + b * y[i] + c * z[i]);

                        boolean pos = false;
                        boolean neg = false;
                        boolean first = true;

                        for (int l = 0; l < n; l++) {
                            long v = a * x[l] + b * y[l] + c * z[l] + d;
                            if (v < 0) neg = true;
                            if (v > 0) pos = true;
                            if (v == 0 && l < k && l != i && l != j) {
                                first = false;
                            }
                        }
                        if (!(pos && neg) && first) {
                            faces.add(new Plane(a, b, c, d));
                        }
                    }
                }
            }

            double cx = 0;
            double cy = 0;
            double cz = 0;
            double vol = 0;
            for (Plane f : faces) {
                ArrayList<Integer> points = new ArrayList<Integer>();
                for (int i = 0; i < n; i++) {
                    if (f.a * x[i] + f.b * y[i] + f.c * z[i] + f.d == 0) {
                        points.add(i);
                    }
                }

                System.err.println(Arrays.toString(points.toArray()));

                int p1 = points.get(0);
                int p2 = points.get(1);
                double ix = x[p2] - x[p1];
                double iy = y[p2] - y[p1];
                double iz = z[p2] - z[p1];
                double dd = sqrt(ix * ix + iy * iy + iz * iz);
                ix /= dd;
                iy /= dd;
                iz /= dd;

                double kx = f.a;
                double ky = f.b;
                double kz = f.c;
                dd = sqrt(kx * kx + ky * ky + kz * kz);
                kx /= dd;
                ky /= dd;
                kz /= dd;

                double jx = iy * kz - iz * ky;
                double jy = iz * kx - ix * kz;
                double jz = ix * ky - iy * kx;

                Point2D[] p = new Point2D[points.size()];
                for (int j = 0; j < points.size(); j++) {
                    int i = points.get(j);
                    double dx = x[i] - x[p1];
                    double dy = y[i] - y[p1];
                    double dz = z[i] - z[p1];
                    p[j] = new Point2D(dx * ix + dy * iy + dz * iz, dx * jx + dy * jy + dz * jz);
                    assert abs(dx * kx + dy * ky + dz * kz) < EPS;
                }

                Arrays.sort(p);
//                System.err.println(Arrays.toString(p));

                double s = 0;
                double rx = 0;
                double ry = 0;
                int m = p.length;
                for (int i = 2; i < m; i++) {
                    double ts = p[i].x * p[i - 1].y - p[i].y * p[i - 1].x;
                    s += ts;
                    rx += (p[i].x + p[i - 1].x) * ts;
                    ry += (p[i].y + p[i - 1].y) * ts;
                }
                rx /= 3.0 * s;
                ry /= 3.0 * s;
                s = abs(s);

                double rx3 = minx + (x[p1] + ix * rx + jx * ry - minx) * 0.75;
                double ry3 = miny + (y[p1] + iy * rx + jy * ry - miny) * 0.75;
                double rz3 = minz + (z[p1] + iz * rx + jz * ry - minz) * 0.75;

                double d = (minx * f.a + miny * f.b + minz * f.c + f.d) / f.norm;
                d = abs(d);

                double dvol = d * s / 6.0;
                cx += rx3 * dvol;
                cy += ry3 * dvol;
                cz += rz3 * dvol;
                vol += dvol;
            }

            assert vol > 0.1;
            System.err.println(vol * 4.0 / 3.0);

            cx /= vol;
            cy /= vol;
            cz /= vol;

            System.err.println(cx + " " + cy + " " + cz);
            double mind = Double.POSITIVE_INFINITY;
            for (Plane f : faces) {
                double d = (cx * f.a + cy * f.b + cz * f.c + f.d) / f.norm;
                d = abs(d);
                if (d < mind) {
                    mind = d;
                }
            }
//            System.err.println(mind);
            return mind;
        }
    }

    public void solve() throws IOException {
        Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out);

        Polyhedron p = new Polyhedron(in);
        Polyhedron q = new Polyhedron(in);

        double ans = p.dist() + q.dist();
//        System.err.println(ans);
        out.println(ans);

        in.close();
        out.close();
    }

    public void run() {
        try {
            solve();
        } catch (Exception e) {
            e.printStackTrace(System.err);
            System.exit(64);
        }
    }

    public static void main(String[] arg) throws Exception {
//        new asteroids_rs().run();
        new asteroids_as().run();
    }
}
