// Accepted on PKU

import java.io.*;
import java.util.*;

public class asteroids_rs2 implements Runnable {
    private BufferedReader in;
    private PrintWriter out;
   
    private void check(boolean expr, String msg) {
        if (!expr) {
            throw new Error(msg);
        }
    }
   
    private void checkBounds(int n, int low, int hi, String nStr) {
        check((low <= n) && (n <= hi), nStr + " is not in [" + low + ", " + hi + "]");
    }
   
    private class Polyhedron {
        private int[] x, y, z;
        private int n;
        private List<List<Integer>> facets;
        private long vpa, vpb, vpc, vpd;
        private double xc, yc, zc;
        private double minDist;
       
        private void vectorProduct(int i, int j, int k) {
            int dx1 = x[j] - x[i];
            int dy1 = y[j] - y[i];
            int dz1 = z[j] - z[i];
            int dx2 = x[k] - x[i];
            int dy2 = y[k] - y[i];
            int dz2 = z[k] - z[i];
            vpa = dy1 * dz2 - dy2 * dz1;
            vpb = -(dx1 * dz2 - dx2 * dz1);
            vpc = dx1 * dy2 - dx2 * dy1;
            vpd = -vpa * x[i] - vpb * y[i] - vpc * z[i];
        }
       
        private void checkConvexFacet(long a, long b, long c, long d, List<Integer> facet) {
            int m = facet.size();
            int num1 = facet.get(0);
            for (int i = 1; i < m; i++) {
                for (int j = 1; j + 1 < m; j++) {
                    int num2 = facet.get(j);
                    int num3 = facet.get(j + 1);
                    vectorProduct(num1, num2, num3);
                    long sp = a * vpa + b * vpb + c * vpc;
                    check(sp != 0, "Three points on a line");
                    if (sp < 0) {
                        facet.set(j, num3);
                        facet.set(j + 1, num2);
                    }
                }
            }
            for (int i = 0; i < m; i++) {
                for (int j = i + 1; j < m; j++) {
                    for (int k = j + 1; k < m; k++) {
                        vectorProduct(facet.get(i), facet.get(j), facet.get(k));
                        long sp = a * vpa + b * vpb + c * vpc;
                        check(sp > 0, "Facet not convex");
                    }
                }
            }
        }
       
        public Polyhedron() throws IOException {
            n = Integer.parseInt(in.readLine());
            checkBounds(n, 1, 100, "n");
            x = new int[n];
            y = new int[n];
            z = new int[n];
            for (int i = 0; i < n; i++) {
                StringTokenizer st = new StringTokenizer(in.readLine());
                x[i] = Integer.parseInt(st.nextToken());
                y[i] = Integer.parseInt(st.nextToken());
                z[i] = Integer.parseInt(st.nextToken());
            }
           
            facets = new ArrayList<List<Integer>>();
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    LOOPK:
                    for (int k = j + 1; k < n; k++) {
                        vectorProduct(i, j, k);
                        final long a = vpa;
                        final long b = vpb;
                        final long c = vpc;
                        final long d = vpd;
                       
                        boolean negative = false;
                        boolean positive = false;
                        for (int u = 0; u < n; u++) {
                            long dist = a * x[u] + b * y[u] + c * z[u] + d;
                            if (dist < 0) {
                                negative = true;
                            } else if (dist > 0) {
                                positive = true;
                            } else {
                                if ((u < k) && (u != i) && (u != j)) {
                                    continue LOOPK;
                                }
                            }
                        }
                        if (positive && negative) {
                            continue;
                        }
                       
                        final List<Integer> facet = new ArrayList<Integer>();
                        facet.add(i);
                        facet.add(j);
                        facet.add(k);
                        for (int u = k + 1; u < n; u++) {
                            if (a * x[u] + b * y[u] + c * z[u] + d == 0) {
                                facet.add(u);
                            }
                        }
//                        System.err.println(Arrays.toString(facet.toArray()));
                        //checkConvexFacet(a, b, c, d, facet);
                        Collections.sort(facet, new Comparator<Integer>() {
                        	@Override
                        	public int compare(Integer num2, Integer num3) {
                        	    int num1 = facet.get(0);
                        	    vectorProduct(num1, num2, num3);
                                long sp = a * vpa + b * vpb + c * vpc;
                        		return -1 * (new Long(sp)).compareTo(0L);
                        	}
                        });

                        facets.add(facet);
                    }
                }
            }
            check(facets.size() > 1, "polyhedron is degenerate");
           
            long totalVolume = 0;
            long x0 = 0;
            long y0 = 0;
            long z0 = 0;
            for (List<Integer> facet: facets) {
                int m = facet.size();
                int num1 = facet.get(0);
                for (int i = 0; i < m; i++) {
                    int num2 = facet.get(i);
                    int num3 = facet.get((i + 1) % m);
                    long volume = calcVolume(0, num1, num2, num3);
                    totalVolume += volume;
                    x0 += Math.abs(volume) * (x[num1] + x[num2] + x[num3] + x[0]);
                    y0 += Math.abs(volume) * (y[num1] + y[num2] + y[num3] + y[0]);
                    z0 += Math.abs(volume) * (z[num1] + z[num2] + z[num3] + z[0]);
                }
            }
            xc = 1.0 * x0 / totalVolume / 4.0;
            yc = 1.0 * y0 / totalVolume / 4.0;
            zc = 1.0 * z0 / totalVolume / 4.0;
//            System.err.println(xc + " " + yc + " " + zc);
//            System.err.println(totalVolume);
           
            minDist = Double.MAX_VALUE;
            for (List<Integer> facet: facets) {
                vectorProduct(facet.get(0), facet.get(1), facet.get(2));
                double norm = Math.sqrt(vpa * vpa + vpb * vpb + vpc * vpc);
                double dist = (vpa * xc + vpb * yc + vpc * zc + vpd) / norm;
                minDist = Math.min(minDist, Math.abs(dist));
            }
        }

        private long calcVolume(int a, int b, int c, int d) {
            vectorProduct(a, c, d);
            return Math.abs((x[b] - x[a]) * vpa + (y[b] - y[a]) * vpb + (z[b] - z[a]) * vpc);
        }
    }
   
    private void solve() throws IOException {
        Polyhedron p1 = new Polyhedron();
        Polyhedron p2 = new Polyhedron();
        out.printf("%.6f\n", p1.minDist + p2.minDist);
    }
   
    public static void main(String[] args) {
        new Thread(new asteroids_rs2()).start();
    }

    public void run() {
        String problem = getClass().getName().split("_")[0];
        try {
            Locale.setDefault(Locale.US);
            in = new BufferedReader(new  InputStreamReader(System.in));
            out = new PrintWriter(System.out);
            solve();
            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }
}
