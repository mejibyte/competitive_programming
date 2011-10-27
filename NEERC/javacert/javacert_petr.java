import java.io.BufferedReader;
import java.io.FileReader;
import java.io.PrintWriter;
import java.io.IOException;
import java.util.StringTokenizer;

public class javacert_petr implements Runnable {
    private void solve() throws IOException {
        int k = nextInt();
        int n = nextInt();
        int m = nextInt();
        int[] p = new int[m];
        for (int i = 0; i < m; ++i) {
            p[i] = nextInt();
        }
        int nmin = 1;
        int nmax = 1;
        int bestDelta = Integer.MAX_VALUE;
        int[][] bestRes = null;
        while (nmax <= n) {
            int[][] res = canSolve(k, n, m, p, nmin, nmax);
            if (res != null) {
                if (nmax - nmin < bestDelta) {
                    bestDelta = nmax - nmin;
                    bestRes = res;
                }
                ++nmin;
                if (nmin > nmax) {
                    ++nmax;
                }
            } else {
                ++nmax;
            }
        }
        for (int i = 0; i < m; ++i) {
            writer.println(bestRes[i][0] + " " + bestRes[i][1]);
        }
    }

    private int[][] canSolve(int k, int n, int m, int[] p, int nmin, int nmax) {
        boolean[][][] can = new boolean[m + 1][n + 1][k + 1];
        can[0][0][0] = true;
        for (int i = 0; i < m; ++i) {
            for (int cn = nmin; cn <= nmax; ++cn) {
                for (int ck = 0; ck <= cn; ++ck)
                    if (divide(100 * ck, cn) == p[i]) {
                        for (int pn = 0; pn + cn <= n; ++pn)
                            for (int pk = 0; pk <= pn && pk + ck <= k; ++pk)
                                if (can[i][pn][pk])
                                    can[i + 1][pn + cn][pk + ck] = true;
                    }
            }
        }
        if (!can[m][n][k])
            return null;
        int[][] res = new int[m][2];
        for (int i = m - 1; i >= 0; --i) {
            outer: for (int cn = nmin; cn <= nmax; ++cn) {
                for (int ck = 0; ck <= cn; ++ck)
                    if (divide(100 * ck, cn) == p[i] && ck <= k && cn <= n) {
                        if (can[i][n - cn][k - ck]) {
                            n -= cn;
                            k -= ck;
                            res[i][0] = cn - ck;
                            res[i][1] = cn;
                            break outer;
                        }
                    }
            }
        }
        return res;
    }

    private int divide(int a, int b) {
        int rem = a % b;
        if (2 * rem < b)
            return a / b;
        if (2 * rem > b)
            return a / b + 1;
        int z = a / b;
        if (z % 2 != 0)
            ++z;
        return z;
    }


    public static void main(String[] args) throws InterruptedException {
        Thread thread = new Thread(new javacert_petr());
        thread.start();
        thread.join();
    }

    static final String TASK_ID = "javacert";
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
