import java.io.*;
import java.util.*;

public class inspection_rs implements Runnable {
    private BufferedReader in;
    private PrintWriter out;
    
    private void check(boolean expr, String msg) {
        if (!expr) {
            throw new Error(msg);
        }
    }
    
    private void checkBounds(int n, int low, int hi, String nStr) {
        check((low <= n) && (n <= hi), nStr + " is not in [" + low + ", " + hi + "]");
    }
    
    private boolean[][] go, w;
    private int[][] flow, cap, ans;
    private boolean[] mark;
    private int[] path;
    private int n, count;
    
    private static final int MAXW = 10000;
    
    private void solve() throws IOException {
        n = Integer.parseInt(in.readLine());
        checkBounds(n, 1, 100, "n");
        go = new boolean[n][n];
        w = new boolean[n][n];
        for (int i = 0; i < n; i++) {
            StringTokenizer st = new StringTokenizer(in.readLine());
            int w = Integer.parseInt(st.nextToken());
            for (int j = 0; j < w; j++) {
                int u = Integer.parseInt(st.nextToken()) - 1;
                check(u != i, "Edge from vertix to itself");
                check(!go[i][u], "Duplicate edges");
                go[i][u] = true;
            }
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    if (w[j][i] && w[i][k]) {
                        w[j][k] = true;
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            check(!w[i][i], "graph is not acyclic");
        }
        
        int s = n;
        int t = n + 1;
        flow = new int[n + 2][n + 2];
        cap = new int[n + 2][n + 2];
        int[][] baseFlow = new int[n + 2][n + 2];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (go[i][j]) {
                    baseFlow[i][j] = MAXW;
                    baseFlow[s][i] += MAXW;
                    baseFlow[j][t] += MAXW;
                    
                    cap[i][j] = MAXW - 1;
                    cap[s][i] += MAXW;
                    cap[j][t] += MAXW;

                    flow[i][j] = MAXW - 1;
                    flow[j][i] = -(MAXW - 1);

                    flow[s][i] += MAXW - 1;
                    flow[i][s] -= MAXW - 1;

                    flow[j][t] += MAXW - 1;
                    flow[t][j] -= MAXW - 1;
                }
            }
        }
        
        int a = 1 << 20;
        n += 2;
        mark = new boolean[n];
        while (a > 0) {
            Arrays.fill(mark, false);
            if (dfs(s, t, a)) {
                continue;
            }
            a = a >> 1;
        }
        ans = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (flow[i][j] < 0) {
                    ans[i][j] = 0;
                } else {
                    ans[i][j] = baseFlow[i][j] - flow[i][j];
                }
            }
        }
        
        int answer = 0;
        for (int i = 0; i < n; i++) {
            answer += ans[s][i];
        }
        out.println(answer);
        
        path = new int[n];
        for (int i = 0; i < n; i++) {
            while (ans[s][i] > 0) {
                Arrays.fill(mark, false);
                count = 0;
                findPath(s, t);
                for (int j = count - 2; j >= 0; j--) {
                    out.print((path[j] + 1) + " ");
                }
                out.println();
            }
        }
    }
        
    
    private boolean findPath(int u, int target) {
        if (u == target) {
            return true;
        }
        mark[u] = true;
        for (int v = 0; v < n; v++) {
            if (ans[u][v] > 0 && !mark[v] && findPath(v, target)) {
                ans[u][v]--;
                path[count++] = u;
                return true;
            }
        }
        return false;
    }

    private boolean dfs(int u, int target, int a) {
        if (u == target) {
            return true;
        }
        mark[u] = true;
        for (int v = 0; v < n; v++) {
            if (!mark[v] && flow[u][v] + a <= cap[u][v] && dfs(v, target, a)) {
                flow[u][v] += a;
                flow[v][u] -= a;
                return true;
            }
        }
        return false;
    }

    public static void main(String[] args) {
        new Thread(new inspection_rs()).start();
    }

    public void run() {
        String problem = getClass().getName().split("_")[0];
        try {
            in = new BufferedReader(new FileReader(new File(problem + ".in")));
            out = new PrintWriter(new File(problem + ".out"));
            solve();
            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }
}
