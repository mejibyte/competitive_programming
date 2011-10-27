import java.io.PrintWriter;
import java.io.FileNotFoundException;
import java.util.*;

public class doall {

    int tn = 0;

    void printTest(String comment, int[] n, int[] w) throws FileNotFoundException {
        tn++;
        System.out.println("Test " + String.format("%02d", tn) + ": " + comment);
        PrintWriter out = new PrintWriter(String.format("%02d", tn));
        int[] p = new int[n.length];
        for (int i = 0; i < n.length; i++) {
            p[i] = (int) Math.rint(100.0 * (n[i] - w[i]) / n[i]);
        }
        int nn = 0;
        int kk = 0;
        for (int i = 0; i < n.length; i++) {
            nn += n[i];
            kk += n[i] - w[i];
        }
        out.println(kk + " " + nn + " " + n.length);
        for (int i = 0; i < n.length; i++) {
            out.println(p[i]);
        }
        out.close();
    }

    Random random = new Random(124234234);


    public static void main(String[] args) {
        try {
            new doall().run();
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private void run() throws Exception {
        printTest("Sample test",
                new int[] {13, 13, 18, 13, 16, 14},
                new int[] {0, 0, 3, 1, 4, 1}
                );

        for (int n = 1; n < 4; n++) {
            for (int k = 0; k <= n; k++) {
                printTest(String.format("One category, n = %d, k = %d", n, k),
                        new int[] {n},
                        new int[] {n - k}
                        );
            }
        }
        for (int n1 = 1; n1 < 3; n1++) {
            for (int k1 = 0; k1 <= n1; k1++) {
                for (int n2 = n1; n2 < 3; n2++) {
                    for (int k2 = 0; k2 <= n2; k2++) {
                        printTest(String.format("Two categories, (%d of %d) and (%d of %d)", k1, n1, k2, n2),
                                new int[] {n1, n2},
                                new int[] {n1 - k1, n2 - k2}
                                );
                    }
                }
            }
        }

        for (int i = 0; i < 10; i++) {
            int m = 10;
            int[] n = new int[m];
            int[] w = new int[m];
            int nn = 0;
            for (int j = 0; j < m; j++) {
                double z;
                do {
                  n[j] = random.nextInt(100) + 1;
                  w[j] = random.nextInt(n[j]);                  
                  z = 100.0 * w[j] / n[j];
                  z = Math.abs(z - Math.round(z));
                } while (Math.abs(z - 0.5) > 1e-9);
                nn += n[j];
                if (nn > 100) {
                    nn -= n[j];
                    m = j;
                    break;
                }                  
            }
            int[] n2 = new int[m];
            int[] w2 = new int[m];
            System.arraycopy(n, 0, n2, 0, m);
            System.arraycopy(w, 0, w2, 0, m);
            printTest("Rounding issues", n2, w2);
        }

        for (int i = 0; i < 10; i++) {
            int m = 5 + random.nextInt(6);
            int nn = 50 + random.nextInt(51);
            int kk = random.nextInt(nn + 1);
            int[] n = new int[m];
            Arrays.fill(n, 1);
            nn -= m;
            while (nn > 0) {
                n[random.nextInt(m)]++;
                nn--;
            }
            int[] w = n.clone();
            while (kk > 0) {
                int x;
                do {
                    x = random.nextInt(m);
                } while (w[x] == 0);
                w[x]--;
                kk--;
            }
            printTest("Random test", n, w);
        }

        {
            int m = 10;
            int[] n = new int[m];
            Arrays.fill(n, 10);
            int[] w = new int[m];
            Arrays.fill(w, 10);
            printTest("100% test", n, w);
        }

        {
            int m = 10;
            int[] n = new int[m];
            Arrays.fill(n, 10);
            int[] w = new int[m];
            Arrays.fill(w, 0);
            printTest("0% test", n, w);
        }

        {
            int m = 10;
            int[] n = new int[m];
            Arrays.fill(n, 10);
            int[] w = new int[m];
            Arrays.fill(w, 5);
            printTest("50% test", n, w);
        }

        for (int i = 0; i < 10; i++) {
            int m = 10;
            int nn = 100;
            int kk = random.nextInt(nn + 1);
            int[] n = new int[m];
            Arrays.fill(n, 1);
            nn -= m;
            while (nn > 0) {
                n[random.nextInt(m)]++;
                nn--;
            }
            int[] w = new int[m];
            for (int j = 0; j < m; j++) {
                int k = random.nextInt(100);
                if (k < 50) {
                    w[j] = n[j];
                } else {
                    w[j] = 0;
                }
            }
            printTest("Random 0, 100 test", n, w);
        }

        for (int i = 0; i < 10; i++) {
            int m = 10;
            int nn = 100;
            int kk = random.nextInt(nn + 1);
            int[] n = new int[m];
            Arrays.fill(n, 1);
            nn -= m;
            while (nn > 0) {
                n[random.nextInt(m)]++;
                nn--;
            }
            int[] w = new int[m];
            for (int j = 0; j < m; j++) {
                int k = random.nextInt(100);
                if (k < 20) {
                    w[j] = random.nextInt(n[j] + 1);
                } else if (k < 60) {
                    w[j] = n[j];
                } else {
                    w[j] = 0;
                }
            }
            printTest("Random 0, 100, x test", n, w);
        }

        for (int i = 0; i < 10; i++) {
            int m = 10;
            int nn = 100;
            int kk = random.nextInt(nn + 1);
            int[] n = new int[m];
            Arrays.fill(n, 1);
            nn -= m;
            while (nn > 0) {
                n[random.nextInt(m)]++;
                nn--;
            }
            int[] w = n.clone();
            while (kk > 0) {
                int x;
                do {
                    x = random.nextInt(m);
                } while (w[x] == 0);
                w[x]--;
                kk--;
            }
            printTest("Big random test", n, w);
        }

    }

}
