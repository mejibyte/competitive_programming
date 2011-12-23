import java.io.*;
import java.util.*;

public class asteroids_mb implements Runnable {
    private static final double EPSILON = 1e-6;

    static class Point3d {
        public final double x;
        public final double y;
        public final double z;

        public Point3d(double x, double y, double z) {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        public static Point3d read(Scanner in) {
            final int x = in.nextInt();
            final int y = in.nextInt();
            final int z = in.nextInt();
            return new Point3d(x, y, z);
        }
    }

    static class Plane3d implements Comparable<Plane3d> {
        public double a;
        public double b;
        public double c;
        public double d;

        public Plane3d(Point3d p1, Point3d p2, Point3d p3) {
            a = (p2.y - p1.y) * (p3.z - p1.z) - (p3.y - p1.y) * (p2.z - p1.z);
            b = (p2.z - p1.z) * (p3.x - p1.x) - (p3.z - p1.z) * (p2.x - p1.x);
            c = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
            d = -(a * p1.x + b * p1.y + c * p1.z);
            final double norm = Math.sqrt(a * a + b * b + c * c);
            a /= norm;
            b /= norm;
            c /= norm;
            d /= norm;

            if (a < 0 || Math.abs(a) < EPSILON && b < 0 || Math.abs(a) < EPSILON && Math.abs(b) < EPSILON && c < 0) {
                a = -a;
                b = -b;
                c = -c;
                d = -d;
            }
        }

        public double getDist(Point3d origin) {
            return a * origin.x + b * origin.y + c * origin.z + d; 
        }

        public int compareTo(Plane3d o) {
            if (a < o.a - EPSILON) {
                return -1;
            }
            if (a > o.a + EPSILON) {
                return +1;
            }
            if (b < o.b - EPSILON) {
                return -1;
            }
            if (b > o.b + EPSILON) {
                return +1;
            }
            if (c < o.c - EPSILON) {
                return -1;
            }
            if (c > o.c + EPSILON) {
                return +1;
            }
            if (d < o.d - EPSILON) {
                return -1;
            }
            if (d > o.d + EPSILON) {
                return +1;
            }
            return 0;
        }
    }

    static class Face {
        public final Plane3d p;
        public final Point3d[] v;

        public Face(Plane3d p, Point3d[] v) {
            this.p = p;
            this.v = v;
        }
    }

    static class Polyhedron {
        private final Point3d[] vertices;

        public Polyhedron(Point3d[] vertices) {
            this.vertices = vertices;
        }

        public static Polyhedron read(Scanner in) {
            final int n = in.nextInt();
            Point3d[] vertices = new Point3d[n];
            for (int i = 0; i < n; i++) {
                vertices[i] = Point3d.read(in);
            }
            return new Polyhedron(vertices);
        }

        public double getDist() {
            ArrayList<Face> faces = new ArrayList<Face>();
            TreeSet<Plane3d> facePlanes = new TreeSet<Plane3d>();
            for (int i = 0; i < vertices.length; i++) {
                Point3d v1 = vertices[i];
                for (int j = i + 1; j < vertices.length; j++) {
                    Point3d v2 = vertices[j];
                    for (int k = j + 1; k < vertices.length; k++) {
                        Point3d v3 = vertices[k];
                        Plane3d p = new Plane3d(v1, v2, v3);
                        if (!facePlanes.contains(p)) {
                            final Face face = buildFace(p);
                            if (face != null) {
                                faces.add(face);
                                facePlanes.add(p);
                            }
                        }
                    }
                }
            }

            double dist = Double.MAX_VALUE;
            final Point3d centerOfMass = getCenterOfMass(faces);
            System.out.printf("Center of mass = (%.0f, %.0f, %.0f)\n", centerOfMass.x, centerOfMass.y, centerOfMass.z);
            for (Face f : faces) {
                dist = Math.min(dist, Math.abs(f.p.getDist(centerOfMass)));                
            }
            System.out.println(dist);
            return dist;
        }

        private Point3d getCenterOfMass(ArrayList<Face> faces) {
            double x = 0;
            double y = 0;
            double z = 0;
            double vol = 0;
            final Point3d p1 = vertices[0];
            for (Face f : faces) {
                Point3d p2 = f.v[0];
                for (int i = 1; i < f.v.length - 1; i++) {
                    Point3d p3 = f.v[i];
                    Point3d p4 = f.v[i + 1];
                    final double thisVol = getVolume(p1, p2, p3, p4);
                    final Point3d thisCentroid = getCentroid(p1, p2, p3, p4);
                    vol += thisVol;
                    x += thisVol * thisCentroid.x;
                    y += thisVol * thisCentroid.y;
                    z += thisVol * thisCentroid.z;
                }
            }
            return new Point3d(x / vol, y / vol, z / vol);
        }

        private Point3d getCentroid(Point3d p1, Point3d p2, Point3d p3, Point3d p4) {
            return new Point3d(
                    (p1.x + p2.x + p3.x + p4.x) / 4,
                    (p1.y + p2.y + p3.y + p4.y) / 4,
                    (p1.z + p2.z + p3.z + p4.z) / 4);
        }

        private double getVolume(Point3d p1, Point3d p2, Point3d p3, Point3d p4) {
            final double dx1 = p2.x - p1.x;
            final double dy1 = p2.y - p1.y;
            final double dz1 = p2.z - p1.z;
            final double dx2 = p3.x - p1.x;
            final double dy2 = p3.y - p1.y;
            final double dz2 = p3.z - p1.z;
            final double dx3 = p4.x - p1.x;
            final double dy3 = p4.y - p1.y;
            final double dz3 = p4.z - p1.z;
            return Math.abs(
                (dx1 * (dy2 * dz3 - dz2 * dy3) -
                dy1 * (dx2 * dz3 - dz2 * dx3) +
                dz1 * (dx2 * dy3 - dy2 * dx3))) / 6.0;
        }

        private Face buildFace(Plane3d p) {
            final ArrayList<Point3d> verticesList = new ArrayList<Point3d>();
            boolean positive = false;
            boolean negative = false;
            for (int i = 0; i < vertices.length; i++) {
                final Point3d v = vertices[i];
                double dist = p.getDist(v);
                if (Math.abs(dist) > EPSILON) {
                    if (dist > 0) {
                        positive = true;
                    } else {
                        negative = true;
                    }
                    if (positive && negative) {
                        return null;
                    }
                } else {
                    verticesList.add(v);
                }
            }

            final Point3d[] vertices = new Point3d[verticesList.size()];
            verticesList.toArray(vertices);
            final AngleComparator angleComparator = new AngleComparator(p, vertices[0]);
            Arrays.sort(vertices, 1, vertices.length, angleComparator);
            return new Face(p, vertices);
        }
    }

    static class AngleComparator implements Comparator<Point3d> {
        private final double nxx;
        private final double nxy;
        private final double nxz;
        private final double nyx;
        private final double nyy;
        private final double nyz;
        private final double x0;
        private final double y0;

        AngleComparator(Plane3d p, Point3d origin) {
            if (Math.abs(p.a) > EPSILON || Math.abs(p.b) > EPSILON) {
                nxx = -p.b;
                nxy = p.a;
                nxz = 0;
            } else {
                nxx = 0;
                nxy = -p.c;
                nxz = p.b;
            }

            nyx = nxy * p.c - nxz * p.b;
            nyy = nxz * p.a - nxx * p.c;
            nyz = nxx * p.b - nxy * p.a;

            assert Math.abs(p.a * nxx + p.b * nxy + p.c * nxz) < EPSILON;
            assert Math.abs(p.a * nyx + p.b * nyy + p.c * nyz) < EPSILON;

            x0 = origin.x * nxx + origin.y * nxy + origin.z * nxz;
            y0 = origin.x * nyx + origin.y * nyy + origin.z * nyz;
        }

        public int compare(Point3d o1, Point3d o2) {
            final double x1 = o1.x * nxx + o1.y * nxy + o1.z * nxz - x0;
            final double y1 = o1.x * nyx + o1.y * nyy + o1.z * nyz - y0;
            final double x2 = o2.x * nxx + o2.y * nxy + o2.z * nxz - x0;
            final double y2 = o2.x * nyx + o2.y * nyy + o2.z * nyz - y0;
            final double prod = x1 * y2 - x2 * y1;
            if (prod < -EPSILON) {
                return -1;
            } else if (prod > EPSILON) {
                return +1;
            } else {
                return 0;
            }
        }
    }

    public static void main(String[] args) {
        new Thread(new asteroids_mb()).start();
    }

    public void run() {
        try {
            final Scanner in = new Scanner(System.in);
            final PrintWriter out = new PrintWriter(System.out);

            Polyhedron p1 = Polyhedron.read(in);
            Polyhedron p2 = Polyhedron.read(in);

            out.println(p1.getDist() + p2.getDist());

            in.close();
            out.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
