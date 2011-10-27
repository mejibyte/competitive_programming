import java.io.BufferedReader;
import java.io.FileReader;
import java.io.PrintWriter;
import java.io.IOException;
import java.util.StringTokenizer;

public class business_petr implements Runnable {
    private void solve() throws IOException {
        int n = nextInt();
        int m = nextInt();
        int res = Integer.MAX_VALUE;
        for (int i = 0; i < m; ++i) {
            int u = nextInt();
            int d = nextInt();
            int l = -1;
            int r = n + 1;
            while (r > l + 1) {
                int mm = (l + r) / 2;
                int z = mm * u - (n - mm) * d;
                if (z > 0) {
                    r = mm;
                    res = Math.min(res, z);
                } else {
                    l = mm;
                }
            }
        }
        writer.println(res);
    }


    public static void main(String[] args) throws InterruptedException {
        Thread thread = new Thread(new business_petr());
        thread.start();
        thread.join();
    }

    static final String TASK_ID = "business";
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
