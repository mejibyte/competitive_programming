import java.util.Scanner;
import java.util.Arrays;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;

public class inspection_pm {

    private static int[][] f;
    private static boolean[] z;
    private static int n;
    private static int nn;
    private static int[][] c;
    private static int[][] aa;

    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("inspection.in"));
        PrintWriter out = new PrintWriter("inspection.out");

        n = in.nextInt();
        boolean[][] a = new boolean[n][n];
        for (int i = 0; i < n; i++) {
            int k = in.nextInt();
            for (int j = 0; j < k; j++) {
                int x = in.nextInt();
                a[i][x - 1] = true;
            }
        }

        boolean[][] b = new boolean[n][n];
        for (int i = 0; i < n; i++) {
            System.arraycopy(a[i], 0, b[i], 0, n);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    b[j][k] = b[j][k] || b[j][i] && b[i][k];
                }
            }
        }

        int[] d = new int[n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i][j]) {
                    d[i]++;
                    d[j]--;
                }
            }
        }

        nn = 2 * n + 2;
        c = new int[nn][nn];
        f = new int[nn][nn];

        int s = 0;
        for (int i = 0; i < n; i++) {
            if (d[i] < 0) {
                c[0][i + 2] = -d[i];
            }
            if (d[i] > 0) {
                c[i + 2 + n][1] = d[i];
                s += d[i];
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (b[i][j]) {
                    c[i + 2][j + 2 + n] = 1000000000;
                }
            }
        }

        z = new boolean[nn];
        while (dfs(0)) {
            Arrays.fill(z, false);
            s--;
        }

        aa = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i][j]) aa[i][j] = 1;
            }
        }

        z = new boolean[n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < f[i + 2][j + 2 + n]; k++) {
                    Arrays.fill(z, false);
                    if (!addPath(i, j)) {
                        System.out.println("!!!");
                    }
                    d[i]++;
                    d[j]--;
                }
            }
        }

        out.println(s);
        for (int i = 0; i < n; i++) {
            while (d[i] > 0) {
                d[i]--;
                int k = i;
                while (true) {
                    out.print(k + 1);
                    out.print(" ");
                    for (int kk = 0; kk < n; kk++) {
                        if (aa[k][kk] > 0) {
                            aa[k][kk]--;
                            k = kk;
                            break;
                        }
                    }
                    if (d[k] < 0) {
                        d[k]++;
                        out.println(k + 1);
                        break;
                    }
                }
            }
        }

        in.close();
        out.close();
    }

    private static boolean addPath(int i, int j) {
        if (z[i]) return false;
        z[i] = true;
        if (i == j) {
            return true;
        }
        for (int x = 0; x < n; x++) if (aa[i][x] > 0) {
            if (addPath(x, j)) {
                aa[i][x]++;
                return true;
            }
        }
        return false;
    }

    private static boolean dfs(int i) {
        if (z[i]) return false;
        z[i] = true;
        if (i == 1) {
            return true;
        }
        for (int j = 0; j < nn; j++) {
            if (f[i][j] < c[i][j]) {
                if (dfs(j)) {
                    f[i][j]++;
                    f[j][i]--;
                    return true;
                }
            }
        }
        return false;
    }
}
