import java.io.BufferedReader;
import java.io.FileReader;
import java.io.PrintWriter;
import java.io.IOException;
import java.util.*;

public class kequiv_petr implements Runnable {
    class Segment {
        long l;
        long r;

        Segment(long l, long r) {
            this.l = l;
            this.r = r;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;

            Segment segment = (Segment) o;

            if (l != segment.l) return false;
            if (r != segment.r) return false;

            return true;
        }

        @Override
        public int hashCode() {
            int result = (int) (l ^ (l >>> 32));
            result = 31 * result + (int) (r ^ (r >>> 32));
            return result;
        }
    }

    private void solve() throws IOException {
        int n = nextInt();
        Segment[] segments = new Segment[n];
        for (int i = 0; i < n; ++i) {
            long l = nextLong();
            long r = nextLong();
            segments[i] = new Segment(l, r);
        }
        boolean[][] diff = new boolean[10][10];
        long p10 = 1;
        for (int pos = 0; pos <= 18; ++pos) {
            oneStep(segments, p10, diff);
            p10 *= 10;
        }
        boolean[] mark = new boolean[10];
        for (int i = 1; i < 10; ++i)
            if (!mark[i]) {
                for (int j = 1; j < 10; ++j)
                    if (!diff[i][j]) {
                        mark[j] = true;
                        writer.print(j);
                    }
                writer.println();
            }
    }

    private void oneStep(Segment[] segments, long p10, boolean[][] diff) {
        Map<List<Segment>, List<Integer>> allDigits = new HashMap<List<Segment>, List<Integer>>();
        for (int digit = 1; digit < 10; ++digit) {
            List<Segment> cur = new ArrayList<Segment>();
            for (Segment s : segments) {
                long nl = getNext(s.l, p10, digit);
                long nr = getNext(s.r + 1, p10, digit) - 1;
                if (nl <= nr) {
                    if (cur.size() > 0 && cur.get(cur.size() - 1).r >= nl - 1) {
                        cur.set(cur.size() - 1, new Segment(cur.get(cur.size() - 1).l, nr));
                    } else {
                        cur.add(new Segment(nl, nr));
                    }
                }
            }
            List<Integer> list = allDigits.get(cur);
            if (list == null) {
                list = new ArrayList<Integer>();
                allDigits.put(cur, list);
            }
            list.add(digit);
        }
        for (List<Integer> l1 : allDigits.values())
            for (List<Integer> l2 : allDigits.values())
                if (l1 != l2)
                    for (Integer a1 : l1)
                        for (Integer a2 : l2)
                            diff[a1][a2] = true;
    }

    private long getNext(long l, long p10, int digit) {
        long cd = l / p10 % 10;
        if (cd == digit)
            return l / p10 / 10 * p10 + l % p10;
        else if (cd < digit)
            return l / p10 / 10 * p10;
        else
            return (l / p10 / 10 + 1) * p10;
    }


    public static void main(String[] args) throws InterruptedException {
        Thread thread = new Thread(new kequiv_petr());
        thread.start();
        thread.join();
    }

    static final String TASK_ID = "kequiv";
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
