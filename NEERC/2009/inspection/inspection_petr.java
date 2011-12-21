import java.io.BufferedReader;
import java.io.FileReader;
import java.io.PrintWriter;
import java.io.IOException;
import java.util.StringTokenizer;
import java.util.List;
import java.util.ArrayList;

public class inspection_petr implements Runnable {
    static final int INF = 1000000;

    private void solve() throws IOException {
        int n = nextInt();
        boolean[][] e = new boolean[n][n];
        int[] ne = new int[n];
        List<Integer>[][] paths = new List[n][n];
        int res = 0;
        for (int i = 0; i < n; ++i) {
            int m = nextInt();
            paths[i][i] = new ArrayList<Integer>();
            for (int j = 0; j < m; ++j) {
                int b = nextInt() - 1;
                e[i][b] = true;
                paths[i][b] = new ArrayList<Integer>();
                paths[i][b].add(b);
                ++ne[i];
                ++res;
            }
        }
        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    if (paths[i][j] == null && paths[i][k] != null && paths[k][j] != null) {
                        paths[i][j] = new ArrayList<Integer>();
                        paths[i][j].addAll(paths[i][k]);
                        paths[i][j].addAll(paths[k][j]);
                    }
        int[][] c = new int[2 * n + 2][2 * n + 2];
        int s = 2 * n;
        int t = 2 * n + 1;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                if (e[i][j]) {
                    ++c[s][j];
                    ++c[i + n][t];
                }
                if (paths[i][j] != null) {
                    c[i][j + n] = INF;
                }
            }
        int[][] flow = new int[2 * n + 2][2 * n + 2];
        res -= maxFlow(2 * n + 2, s, t, flow, c);
        int[] topological = new int[n];
        for (int i = 0; i < n; ++i)
            topological[i] = -1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                if (ne[j] == 0) {
                    --ne[j];
                    topological[n - 1 - i] = j;
                    for (int k = 0; k < n; ++k)
                        if (e[k][j])
                            --ne[k];
                    break;
                }
        }
        List<List<Integer>>[] ending = new List[n];
        for (int i = 0; i < n; ++i)
            ending[i] = new ArrayList<List<Integer>>();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                if (e[topological[i]][j]) {
                    List<Integer> l = getSome(n, paths, topological[i], ending, flow);
                    if (l == null) {
                        l = new ArrayList<Integer>();
                        l.add(topological[i]);
                    }
                    l.add(j);
                    ending[j].add(l);
                }
        }
        List<List<Integer>> all = new ArrayList<List<Integer>>();
        for (List<List<Integer>> ll : ending)
            all.addAll(ll);
        if (all.size() != res)
            throw new RuntimeException();
        writer.println(all.size());
        for (List<Integer> l : all) {
            boolean first = true;
            for (Integer x : l) {
                if (first)
                    first = false;
                else
                    writer.print(" ");
                writer.print(x + 1);
            }
            writer.println();
        }
    }

    private List<Integer> getSome(int n, List<Integer>[][] paths, int at, List<List<Integer>>[] ending, int[][] flow) {
        for (int i = 0; i < n; ++i)
            if (flow[i][at + n] > 0 && !ending[i].isEmpty()) {
                --flow[i][at + n];
                List<Integer> l = ending[i].get(ending[i].size() - 1);
                ending[i].remove(ending[i].size() - 1);
                l.addAll(paths[i][at]);
                return l;
            }
        return null;
    }

    private int maxFlow(int n, int s, int t, int[][] flow, int[][] c) {
        int res = 0;
        while (true) {
            int by = dfs(n, s, t, flow, c, new boolean[n], INF);
            if (by == 0)
                break;
            res += by;
        }
        return res;
    }

    private int dfs(int n, int at, int t, int[][] flow, int[][] c, boolean[] mark, int by) {
        if (mark[at])
            return 0;
        mark[at] = true;
        if (at == t)
            return by;
        for (int i = 0; i < n; ++i)
            if (flow[at][i] < c[at][i]) {
                int nby = Math.min(by, c[at][i] - flow[at][i]);
                nby = dfs(n, i, t, flow, c, mark, nby);
                if (nby > 0) {
                    flow[at][i] += nby;
                    flow[i][at] -= nby;
                    return nby;
                }
            }
        return 0;
    }
    public static void main(String[] args) throws InterruptedException {
        Thread thread = new Thread(new inspection_petr());
        thread.start();
        thread.join();
    }

    static final String TASK_ID = "inspection";
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
