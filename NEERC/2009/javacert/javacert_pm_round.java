import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;

public class javacert_pm_round {

    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("javacert.in"));
        PrintWriter out = new PrintWriter("javacert.out");

        int k = in.nextInt();
        int n = in.nextInt();
        int m = in.nextInt();
        int[] p = new int[m];
        for (int i = 0; i < m; i++) {
            p[i] = in.nextInt();
        }

        int res = 1000;
        int[] rn = new int[m];
        int[] rw = new int[m];

        for (int low = 1; low <= n / m; low++) {
            int[][][] a = new int[m + 1][n + 1][n + 1];
            int[][][] pn = new int[m + 1][n + 1][n + 1];
            int[][][] pw = new int[m + 1][n + 1][n + 1];
            a[0][0][0] = low;
            for (int i = 0; i < m; i++) {
                for (int n2 = low; n2 <= n; n2++) {
                    int w2 = (int) Math.round((100 - p[i]) * n2 * 0.01);
                    int pp = (int) Math.round(100.0 * (n2 - w2) / n2);
                    if (pp == p[i]) {
                        for (int n1 = 0; n1 + n2 <= n; n1++) {
                            for (int w1 = 0; w1 <= n; w1++) {
                                if (a[i][n1][w1] > 0) {
                                    int r = Math.max(a[i][n1][w1], n2);
                                    if (a[i + 1][n1 + n2][w1 + w2] == 0 ||
                                            a[i + 1][n1 + n2][w1 + w2] > r) {
                                        a[i + 1][n1 + n2][w1 + w2] = r;
                                        pn[i + 1][n1 + n2][w1 + w2] = n2;
                                        pw[i + 1][n1 + n2][w1 + w2] = w2;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (a[m][n][n - k] > 0) {
                if (a[m][n][n - k] - low < res) {
                    res = a[m][n][n - k] - low;
                    int nn = n;
                    int ww = n - k;
                    for (int i = m; i > 0; i--) {
                        int qn = pn[i][nn][ww];
                        int qw = pw[i][nn][ww];
                        rn[i - 1] = qn;
                        rw[i - 1] = qw;
                        nn -= qn;
                        ww -= qw;
                    }
                }
            }
        }
        for (int i = 0; i < m; i++) {
            out.println(rw[i] + " " + rn[i]);
        }
        in.close();
        out.close();
    }
}
