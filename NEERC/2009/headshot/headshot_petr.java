import java.io.BufferedReader;
import java.io.FileReader;
import java.io.PrintWriter;
import java.io.IOException;
import java.util.StringTokenizer;

public class headshot_petr implements Runnable {
    private void solve() throws IOException {
        String s = nextToken();
        int n = s.length();
        int[] a = new int[n];
        for (int i = 0; i < n; ++i) {
            a[i] = s.charAt(i) - '0';
        }
        double p1 = 0;
        int q1 = 0;
        double p2 = 0;
        int q2 = 0;
        for (int i = 0; i < n; ++i) {
            if (a[i] == 0) {
                ++p2;
                if (a[(i + 1) % n] == 0) {
                    ++p1;
                }
                ++q1;
            }
            ++q2;
        }
        if (p1 / q1 > p2 / q2)
            writer.println("SHOOT");
        else if (p1 / q1 < p2 / q2)
            writer.println("ROTATE");
        else
            writer.println("EQUAL");
    }


    public static void main(String[] args) throws InterruptedException {
        Thread thread = new Thread(new headshot_petr());
        thread.start();
        thread.join();
    }

    static final String TASK_ID = "headshot";
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
