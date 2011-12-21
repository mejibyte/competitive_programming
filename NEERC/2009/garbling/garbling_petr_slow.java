import java.io.BufferedReader;
import java.io.FileReader;
import java.io.PrintWriter;
import java.io.IOException;
import java.util.StringTokenizer;

public class garbling_petr_slow implements Runnable {
    class StepDescription {
        int[] perm;
        long[] numWrites;

        StepDescription(int[] perm, long[] numWrites) {
            this.perm = perm;
            this.numWrites = numWrites;
        }
    }

    private void solve() throws IOException {
        int r = nextInt();
        int c = nextInt();
        long n = nextLong();
        String[] map = new String[r - 1];
        for (int i = 0; i < r - 1; ++i)
            map[i] = nextToken();
        StepDescription fullCycle = buildStepDescription(r, c, n, map, (r - 1) * (c - 1));
        StepDescription remains = buildStepDescription(r, c, n, map, (int) (n % ((r - 1) * (c - 1))));
        StepDescription res = mul(pow(fullCycle, n / ((r - 1) * (c - 1))), remains);
        for (int i = 0; i < r * c; ++i)
            writer.println(res.numWrites[i]);
    }

    private StepDescription mul(StepDescription a, StepDescription b) {
        int[] perm = new int[a.perm.length];
        long[] numWrites = new long[a.perm.length];
        for (int i = 0; i < a.perm.length; ++i) {
            perm[i] = a.perm[b.perm[i]]; 
            numWrites[i] += a.numWrites[i];
            numWrites[a.perm[i]] += b.numWrites[i];
        }
        return new StepDescription(perm, numWrites);
    }

    private StepDescription pow(StepDescription a, long k) {
        if (k == 0) {
            int[] perm = new int[a.perm.length];
            for (int i = 0; i < a.perm.length; ++i)
                perm[i] = i;
            long[] numWrites = new long[a.perm.length];
            return new StepDescription(perm, numWrites);
        } else if (k % 2 == 0) {
            return pow(mul(a, a), k / 2);
        } else {
            return mul(pow(a, k - 1), a);
        }
    }

    private StepDescription buildStepDescription(int r, int c, long n, String[] map, int amount) {
        int[] sperm = new int[r * c];
        for (int i = 0; i < r * c; ++i)
            sperm[i] = i;
        long[] snumWrites = new long[r * c];
        outer: for (int sr = 0; sr < r - 1; ++sr)
            for (int sc = 0; sc < c - 1; ++sc) {
                if (amount == 0)
                    break outer;
                ++snumWrites[sperm[sr * c + sc]];
                switch (map[sr].charAt(sc)) {
                    case 'R': {
                        int t = sperm[sr * c + sc];
                        sperm[sr * c + sc] = sperm[(sr + 1) * c + sc];
                        sperm[(sr + 1) * c + sc] = sperm[(sr + 1) * c + sc + 1];
                        sperm[(sr + 1) * c + sc + 1] = sperm[sr * c + sc + 1];
                        sperm[sr * c + sc + 1] = t;
                        break;
                    }

                    case 'L': {
                        int t = sperm[sr * c + sc];
                        sperm[sr * c + sc] = sperm[sr * c + sc + 1];
                        sperm[sr * c + sc + 1] = sperm[(sr + 1) * c + sc + 1];
                        sperm[(sr + 1) * c + sc + 1] = sperm[(sr + 1) * c + sc];
                        sperm[(sr + 1) * c + sc] = t;
                        break;
                    }
                }
                --amount;
            }
        return new StepDescription(sperm, snumWrites);
    }


    public static void main(String[] args) throws InterruptedException {
        Thread thread = new Thread(new garbling_petr_slow());
        thread.start();
        thread.join();
    }

    static final String TASK_ID = "garbling";
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
