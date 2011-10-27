import java.io.BufferedReader;
import java.io.FileReader;
import java.io.PrintWriter;
import java.io.IOException;
import java.util.StringTokenizer;

public class exclusive_petr implements Runnable {
    private void solve() throws IOException {
        int n = nextInt();
        int m = 'Z' - 'L' + 1;
        boolean[][] e = new boolean[m][m];
        int[][] edges = new int[n][];
        for (int i = 0; i < n; ++i) {
            int a = nextToken().charAt(0) - 'L';
            int b = nextToken().charAt(0) - 'L';
            edges[i] = new int[]{a, b};
            e[a][b] = true;
            e[b][a] = true;
        }
        boolean[] sane = new boolean[1 << m];
        for (int i = 0; i < sane.length; ++i) {
            sane[i] = true;
            for (int j = 0; j < m; ++j)
                if (((i >> j) & 1) != 0)
                    for (int k = j + 1; k < m; ++k)
                        if (((i >> k) & 1) != 0)
                            if (e[j][k])
                                sane[i] = false;
        }
        int[] cnt = new int[1 << m];
        int[] prev = new int[1 << m];
        cnt[0] = 0;
        for (int i = 1; i < cnt.length; ++i) {
            cnt[i] = Integer.MAX_VALUE;
            prev[i] = -1;
            for (int j = i; j > 0; j = (j - 1) & i) {
                if (sane[j]) {
                    if (cnt[i ^ j] + 1 < cnt[i]) {
                        cnt[i] = cnt[i ^ j] + 1;
                        prev[i] = j;
                    }
                }
            }
        }
        int[] step = new int[m];
        int cur = cnt.length - 1;
        while (cur > 0) {
            int set = prev[cur];
            for (int j = 0; j < m; ++j)
                if (((set >> j) & 1) != 0)
                    step[j] = cnt[cur];
            cur ^= set;
        }
        writer.println(cnt[cnt.length - 1] - 2);
        for (int i = 0; i < n; ++i)
            if (step[edges[i][0]] < step[edges[i][1]]) {
                writer.println((char) ('L' + edges[i][0]) + " " + (char) ('L' + edges[i][1]));
            } else {
                writer.println((char) ('L' + edges[i][1]) + " " + (char) ('L' + edges[i][0]));
            }
    }


    public static void main(String[] args) throws InterruptedException {
        Thread thread = new Thread(new exclusive_petr());
        thread.start();
        thread.join();
    }

    static final String TASK_ID = "exclusive";
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
