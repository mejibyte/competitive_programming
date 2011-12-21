import java.io.BufferedReader;
import java.io.FileReader;
import java.io.PrintWriter;
import java.io.IOException;
import java.util.StringTokenizer;
import java.util.Set;
import java.util.Map;
import java.util.HashMap;

public class database_petr implements Runnable {
    private void solve() throws IOException {
        int n = nextInt();
        int m = nextInt();
        Map<Long, Integer>[][] sets = new Map[m][m];
        for (int i = 0; i < m; ++i)
            for (int j = i + 1; j < m; ++j)
                sets[i][j] = new HashMap<Long, Integer>();
        for (int l = 0; l < n; ++l) {
            String s = reader.readLine();
            String[] p = s.split(",");
            long[] h = new long[p.length];
            for (int i = 0; i < p.length; ++i)
                h[i] = getHash(p[i]);
            if (p.length != m)
                throw new RuntimeException();
            for (int i = 0; i < m; ++i)
                for (int j = i + 1; j < m; ++j) {
                    long st = h[i] * 597431956418123L + h[j];
                    if (sets[i][j].containsKey(st)) {
                        writer.println("NO");
                        writer.println((sets[i][j].get(st) + 1) + " " + (l + 1));
                        writer.println((i + 1) + " " + (j + 1));
                        return;
                    }
                    sets[i][j].put(st, l);
                }
        }
        writer.println("YES");
    }

    private long getHash(String s) {
        long res = 1;
        for (int i = 0; i < s.length(); ++i)
            res = res * 3137 + s.charAt(i);
        return res;
    }


    public static void main(String[] args) throws InterruptedException {
        Thread thread = new Thread(new database_petr());
        thread.start();
        thread.join();
    }

    static final String TASK_ID = "database";
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
