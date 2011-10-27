import java.util.Scanner;
import java.util.Random;
import java.io.PrintWriter;
import java.io.FileNotFoundException;
import static java.lang.Math.*;

/**
 * doallSpecial
 *
 * @author Andrew Stankevich
 */
public class doall {
    class Polyhedron {
        int n;
        int[] x;
        int[] y;
        int[] z;

        Polyhedron(int[][] v) {
            n = v.length;
            x = new int[n];
            y = new int[n];
            z = new int[n];
            for (int i = 0; i < n; i++) {
                x[i] = v[i][0];
                y[i] = v[i][1];
                z[i] = v[i][2];
            }
        }

        Polyhedron(int[] x, int[] y, int[] z) {
            n = x.length;
            this.x = x.clone();
            this.y = y.clone();
            this.z = z.clone();
        }

        Polyhedron(int n) {
            this.n = n;
            x = new int[n];
            y = new int[n];
            z = new int[n];
        }

        void shuffleVertices() {
            for (int i = 0; i < n; i++) {
                int j = rnd.nextInt(i + 1);
                int t = x[i]; x[i] = x[j]; x[j] = t;
                t = y[i]; y[i] = y[j]; y[j] = t;
                t = z[i]; z[i] = z[j]; z[j] = t;
            }
        }

        void shift(int dx, int dy, int dz) {
            for (int i = 0; i < n; i++) {
                x[i] += dx;
                y[i] += dy;
                z[i] += dz;
            }
        }
        
        boolean isConvex() {
            boolean[] ok = new boolean[n];
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    for (int k = j + 1; k < n; k++) {
                        long a = (y[j] - y[i]) * (z[k] - z[i]) - (y[k] - y[i]) * (z[j] - z[i]);
                        long b = (z[j] - z[i]) * (x[k] - x[i]) - (z[k] - z[i]) * (x[j] - x[i]);
                        long c = (x[j] - x[i]) * (y[k] - y[i]) - (x[k] - x[i]) * (y[j] - y[i]);
                        if (a == 0 && b == 0 && c == 0) {
                            return false;
                        }
                        long d = -(a * x[i] + b * y[i] + c * z[i]);

                        boolean pos = false;
                        boolean neg = false;

                        for (int l = 0; l < n; l++) {
                            long v = a * x[l] + b * y[l] + c * z[l] + d;
                            if (v < 0) neg = true;
                            if (v > 0) pos = true;
                        }
                        if (!(pos && neg)) {
                            ok[i] = ok[j] = ok[k] = true;
                        }
                    }
                }
            }
            for (int i = 0; i < n; i++) {
                if (!ok[i]) {
                    return false;
                }
            }
            return true;
        }
    }

    class Polygon {
        int n;
        int[] x;
        int[] y;

        Polygon(int n) {
            this.n = n;
            x = new int[n];
            y = new int[n];
        }

        boolean isConvex() {
            boolean[] ok = new boolean[n];
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    boolean pos = false;
                    boolean neg = false;
                    int zer = 0;
                    for (int k = 0; k < n; k++) {
                        int vp = (x[j] - x[i]) * (y[k] - y[i]) - (x[k] - x[i]) * (y[j] - y[i]);
                        if (vp > 0) pos = true;
                        if (vp < 0) neg = true;
                        if (vp == 0) zer++;
                    }
                    if (zer > 2) {
                        return false;
                    }
                    if (!(pos && neg)) {
                        ok[i] = ok[j] = true;
                    }
                }
            }
            for (int i = 0; i < n; i++) {
                if (!ok[i]) {
                    return false;
                }
            }
            return true;
        }
    }

    class Vector {
        int x;
        int y;
        int z;

        Vector(int x, int y, int z) {
            this.x = x;
            this.y = y;
            this.z = z;
        }
    }

    int testNo = 1;

    void printTest(Polyhedron a, Polyhedron b) throws FileNotFoundException {
        System.err.println("Printing test " + testNo);
        PrintWriter out = new PrintWriter("" + testNo / 10 + testNo % 10);
        out.println(a.n);
        for (int i = 0; i < a.n; i++) {
            out.println(a.x[i] + " " + a.y[i] + " " + a.z[i]);
        }
        out.println(b.n);
        for (int i = 0; i < b.n; i++) {
            out.println(b.x[i] + " " + b.y[i] + " " + b.z[i]);
        }
        out.close();
        testNo++;
    }

    Random rnd = new Random(5265485256544745L);

    void generateSample() throws FileNotFoundException {
        Polyhedron a = new Polyhedron(
                new int[][]
                        {{0, 0, 0},
                                {0, 0, 1},
                                {0, 1, 0},
                                {0, 1, 1},
                                {1, 0, 0},
                                {1, 0, 1},
                                {1, 1, 0},
                                {1, 1, 1}}
        );
        Polyhedron b = new Polyhedron(
                new int[][]
                        {{0, 0, 5},
                        {1, 0, 6},
                        {-1, 0, 6},
                        {0, 1, 6},
                        {0, -1, 6}}
        );
        printTest(a, b);
    }

    void generateMax() throws FileNotFoundException {
        Polyhedron a = new Polyhedron(
                new int[][]
                        {{0, 0, 0},
                         {0, 0, 1},
                         {0, 1, 0},
                         {0, 1, 1},
                         {1, 0, 0},
                         {1, 0, 1},
                         {1, 1, 0},
                         {1, 1, 1}}
        );
        for (int i = 0; i < 8; i++) {
            a.x[i] = a.x[i] * 9999 + 1;
            a.y[i] = a.y[i] * 9999 + 1;
            a.z[i] = a.z[i] * 9999 + 1;
        }
        Polyhedron b = new Polyhedron(
                new int[][]
                        {{0, 0, 0},
                         {0, 0, 1},
                         {0, 1, 0},
                         {0, 1, 1},
                         {1, 0, 0},
                         {1, 0, 1},
                         {1, 1, 0},
                         {1, 1, 1}}
        );
        for (int i = 0; i < 8; i++) {
            b.x[i] = b.x[i] * 10000 - 10000;
            b.y[i] = b.y[i] * 10000 - 10000;
            b.z[i] = b.z[i] * 10000 - 10000;
        }
        printTest(a, b);
    }

    Polygon generateOval(int n) {
        Polygon r = new Polygon(n);
        do {
            int rx = rnd.nextInt(300) + 1;
            int ry = rnd.nextInt(300) + 1;
            int cx = rnd.nextInt(601) - 300;
            int cy = rnd.nextInt(601) - 300;
            double alpha = 0;
            for (int i = 0; i < n; i++) {
                double beta;
                do {
                    beta = rnd.nextDouble() * (2 * PI - alpha) / (n - i) * 2;
                } while (beta < 1e-3 || alpha + beta > 2 * PI - (n - i) * 1e-3);
                alpha += beta;
                r.x[i] = (int) Math.round(cx + rx * cos(alpha));
                r.y[i] = (int) Math.round(cx + rx * sin(alpha));
            }
        } while (!r.isConvex());
        return r;
    }

    Vector randomVector(int minc, int maxc) {
        return new Vector(rnd.nextInt(maxc - minc + 1) + minc, rnd.nextInt(maxc - minc + 1) + minc, rnd.nextInt(maxc - minc + 1) + minc);
    }

    int det3(int a1, int a2, int a3, int b1, int b2, int b3, int c1, int c2, int c3) {
        return a1 * b2 * c3 + a2 * b3 * c1 + a3 * b1 * c2 - a1 * b3 * c2 - a2 * b1 * c3 - a3 * b2 * c1;  
    }

    Polyhedron generatePyramid(int n) {
        Polygon base = generateOval(n - 1);
        Vector oi, oj, ok;
        do {
            oi = randomVector(-5, 5);
            oj = randomVector(-5, 5);
            ok = randomVector(-5, 5);
        } while (det3(oi.x, oi.y, oi.z, oj.x, oj.y, oj.z, ok.x, ok.y, ok.z) == 0);
        Polyhedron r = new Polyhedron(n);
        for (int i = 0; i < n - 1; i++) {
            r.x[i] = oi.x * base.x[i] + oj.x * base.y[i];
            r.y[i] = oi.y * base.x[i] + oj.y * base.y[i];
            r.z[i] = oi.z * base.x[i] + oj.z * base.y[i];
        }
        int d = rnd.nextInt(100) + 1;
        r.x[n - 1] = ok.x * d;
        r.y[n - 1] = ok.y * d;
        r.z[n - 1] = ok.z * d;
        return r;
    }

    Polyhedron generatePrism(int n) {
        Polygon base = generateOval(n);
        Vector oi, oj, ok;
        do {
            oi = randomVector(-5, 5);
            oj = randomVector(-5, 5);
            ok = randomVector(-5, 5);
        } while (det3(oi.x, oi.y, oi.z, oj.x, oj.y, oj.z, ok.x, ok.y, ok.z) == 0);
        Polyhedron r = new Polyhedron(2 * n);
        int d = rnd.nextInt(50) + 1;
        for (int i = 0; i < n; i++) {
            r.x[i] = oi.x * base.x[i] + oj.x * base.y[i];
            r.y[i] = oi.y * base.x[i] + oj.y * base.y[i];
            r.z[i] = oi.z * base.x[i] + oj.z * base.y[i];
            r.x[n + i] = oi.x * base.x[i] + oj.x * base.y[i] + ok.x * d;
            r.y[n + i] = oi.y * base.x[i] + oj.y * base.y[i] + ok.y * d;
            r.z[n + i] = oi.z * base.x[i] + oj.z * base.y[i] + ok.z * d;
        }
        return r;
    }

    Polyhedron generateEllipsoid(int n) {
        Polyhedron r;
        do {
            Vector oi, oj, ok;
            do {
                oi = randomVector(-500, 500);
                oj = randomVector(-500, 500);
                ok = randomVector(-500, 500);
            } while (det3(oi.x, oi.y, oi.z, oj.x, oj.y, oj.z, ok.x, ok.y, ok.z) == 0);
            r = new Polyhedron(n);
            for (int i = 0; i < n; i++) {
                double phi = rnd.nextDouble() * 2 * PI;
                double rho = rnd.nextDouble() * PI - PI / 2;
                r.x[i] = (int) Math.round(oi.x * cos(phi) * cos(rho) + oj.x * sin(phi) * cos(rho) + ok.x * sin(rho));
                r.y[i] = (int) Math.round(oi.y * cos(phi) * cos(rho) + oj.y * sin(phi) * cos(rho) + ok.y * sin(rho));
                r.z[i] = (int) Math.round(oi.z * cos(phi) * cos(rho) + oj.z * sin(phi) * cos(rho) + ok.z * sin(rho));
            }
        } while (!r.isConvex());
        return r;
    }


    public void run() throws FileNotFoundException {
        generateSample();

        System.err.println("Tetrahedrons");
        for (int i = 1; i <= 5; i++) {
            Polyhedron a = generatePyramid(4);
            Polyhedron b = generatePyramid(4);
            a.shift(-5000, -5000, -5000);
            b.shift(5000, 5000, 5000);
            printTest(a, b);
        }

        System.err.println("Large pyramids");
        for (int i = 1; i <= 6; i++) {
            Polyhedron a = generatePyramid(i * 10);
            Polyhedron b = generatePyramid(i * 10);
            a.shift(-5000, -5000, -5000);
            b.shift(5000, 5000, 5000);
            printTest(a, b);
        }

        System.err.println("Random pyramids");
        for (int i = 1; i <= 5; i++) {
            Polyhedron a = generatePyramid(rnd.nextInt(56) + 4);
            Polyhedron b = generatePyramid(rnd.nextInt(56) + 4);
            a.shift(-5000, -5000, -5000);
            b.shift(5000, 5000, 5000);
            printTest(a, b);
        }

        System.err.println("Triangular prisms");
        for (int i = 1; i <= 5; i++) {
            Polyhedron a = generatePrism(3);
            Polyhedron b = generatePrism(3);
            a.shift(-5000, -5000, -5000);
            b.shift(5000, 5000, 5000);
            printTest(a, b);
        }

        System.err.println("Large prisms");
        for (int i = 1; i <= 5; i++) {
            Polyhedron a = generatePrism(i * 6);
            Polyhedron b = generatePrism(i * 6);
            a.shift(-5000, -5000, -5000);
            b.shift(5000, 5000, 5000);
            printTest(a, b);
        }

        System.err.println("Random prisms");
        for (int i = 1; i <= 5; i++) {
            Polyhedron a = generatePrism(rnd.nextInt(28) + 3);
            Polyhedron b = generatePrism(rnd.nextInt(28) + 3);
            a.shift(-5000, -5000, -5000);
            b.shift(5000, 5000, 5000);
            printTest(a, b);
        }

        System.err.println("Large ellipsoids");
        for (int i = 2; i <= 10; i++) {
            Polyhedron a = generateEllipsoid(5 * i);
            Polyhedron b = generateEllipsoid(5 * i);
            a.shift(-5000, -5000, -5000);
            b.shift(5000, 5000, 5000);
            printTest(a, b);
        }

        System.err.println("Random ellipsoids");
        for (int i = 1; i <= 5; i++) {
            Polyhedron a = generateEllipsoid(10 + rnd.nextInt(51));
            Polyhedron b = generateEllipsoid(10 + rnd.nextInt(51));
            a.shift(-5000, -5000, -5000);
            b.shift(5000, 5000, 5000);
            printTest(a, b);
        }

        generateMax();
    }

    public static void main(String[] args) throws FileNotFoundException {
        new doall().run();
    }
}
