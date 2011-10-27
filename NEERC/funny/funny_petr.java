import java.io.BufferedReader;
import java.io.FileReader;
import java.io.PrintWriter;
import java.io.IOException;
import java.util.*;

public class funny_petr implements Runnable {
    static int[][] wcnt;

    static class State implements Comparable<State> {
        int[] cnt = new int[26];
        int score;

        State(int[] cnt) {
            this.cnt = cnt;
            score = getScore();
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;

            State state = (State) o;

            if (!Arrays.equals(cnt, state.cnt)) return false;

            return true;
        }

        @Override
        public int hashCode() {
            int result = cnt != null ? Arrays.hashCode(cnt) : 0;
            return result;
        }

        public int compareTo(State state) {
            int z = -score + state.score;
            if (z != 0)
                return z;
            for (int i = 0; i < 26; ++i)
                if (cnt[i] != state.cnt[i])
                    return cnt[i] - state.cnt[i];
            return 0;
        }

        public int getScore() {
            score = 0;
            for (int i = 0; i < wcnt.length; ++i) {
                boolean ok = true;
                for (int j = 0; j < 26; ++j)
                    if (cnt[j] > wcnt[i][j]) {
                        ok = false;
                        break;
                    }
                if (ok)
                    ++score;
            }
            return score;
        }
    }

    int n;

    private void solve() throws IOException {
        int n = nextInt();
        int m = nextInt();
        this.n = n;
        String[] w = new String[m];
        for (int i = 0; i < m; ++i) {
            w[i] = nextToken();
        }
        wcnt = new int[m][26];
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < w[i].length(); ++j)
                ++wcnt[i][w[i].charAt(j) - 'A'];
        TreeSet<State> queue = new TreeSet<State>();
        queue.add(new State(new int[26]));
        Set<String> got = new HashSet<String>();
        got.add("");
        got.addAll(Arrays.asList(w));
        List<String> sols = new ArrayList<String>();
        while (sols.size() < n) {
            State cur = queue.first();
            queue.remove(cur);
            addSols(got, sols, cur);
            if (sols.size() >= n)
                break;
            for (int i = 0; i < 26; ++i) {
                int[] z = cur.cnt.clone();
                ++z[i];
                State s = new State(z);
                queue.add(s);
            }
        }
        for (String s : sols)
            writer.println(s);
    }

    private void addSols(Set<String> got, List<String> sols, State cur) {
        rec(got, sols, cur.cnt.clone(), "");
    }

    private boolean rec(Set<String> got, List<String> sols, int[] cnt, String prefix) {
        boolean any = false;
        for (int i = 0; i < 26; ++i)
            if (cnt[i] > 0) {
                --cnt[i];
                if (rec(got, sols, cnt, prefix + (char) ('A' + i)))
                    return true;
                ++cnt[i];
                any = true;
            }
        if (!any) {
            if (!got.contains(prefix)) {
                sols.add(prefix);
                if (sols.size() >= n)
                    return true;
            }
        }
        return false;
    }


    public static void main(String[] args) throws InterruptedException {
        Thread thread = new Thread(new funny_petr());
        thread.start();
        thread.join();
    }

    static final String TASK_ID = "funny";
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
