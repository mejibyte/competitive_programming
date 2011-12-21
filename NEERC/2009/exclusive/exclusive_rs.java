import java.io.*;

public class exclusive_rs implements Runnable {
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
    
    private void solve() throws IOException {
        int n = Integer.parseInt(in.readLine());
        int m = 15;
        checkBounds(n, 1, 100, "n");
        int[] px = new int[n];
        int[] py = new int[n];
        boolean[][] go = new boolean[m][m];
        for (int i = 0; i < n; i++) {
            String line = in.readLine();
            check(line.length() == 3, "invalid line: " + line);
            px[i] = line.charAt(0) - 'L';
            py[i] = line.charAt(2) - 'L';
            checkBounds(px[i], 0, 14, "resource number");
            checkBounds(py[i], 0, 14, "resource number");
            check(px[i] != py[i], "some process has same resources");
            go[px[i]][py[i]] = true;
            go[py[i]][px[i]] = true;
        }
        
        boolean[] isAnticlique = new boolean[1 << m];
        LOOP:
        for (int mask = 0; mask < (1 << m); mask++) {
            isAnticlique[mask] = true;
            for (int i = 0; i < m; i++) {
                for (int j = i + 1; j < m; j++) {
                    if (((mask & (1 << i)) != 0) && ((mask & (1 << j)) != 0) && go[i][j]) {
                        isAnticlique[mask] = false;
                        continue LOOP;
                    }
                }
            }
        }
        
        int[] ans = new int[1 << m];
        int[] prev = new int[1 << m];
        for (int mask = 0; mask < (1 << m); mask++) {
            if (isAnticlique[mask]) {
                ans[mask] = 1;
                prev[mask] = mask;
                continue;
            }
            ans[mask] = m;
            for (int submask = mask; submask > 0; submask = (submask - 1) & mask) {
                if (!isAnticlique[submask]) {
                    continue;
                }
                if (ans[mask ^ submask] + 1 < ans[mask]) {
                    ans[mask] = ans[mask ^ submask] + 1;
                    prev[mask] = submask;
                }
            }
        }
        

        int curMask = (1 << m) - 1;
        out.println(ans[curMask] - 2);
        int count = 0;
        int[] p = new int[m];
        while (curMask > 0) {
            int mask = prev[curMask];
            for (int i = 0; i < m; i++) {
                if ((mask & (1 << i)) != 0) {
                    p[i] = count++;
                }
            }
            curMask ^= mask;
        }
        for (int i = 0; i < n; i++) {
            if (p[px[i]] < p[py[i]]) {
                out.println((char) ('L' + px[i]) + " " + (char) ('L' + py[i]));
            } else {
                out.println((char) ('L' + py[i]) + " " + (char) ('L' + px[i]));
            }
        }
    }
    
    public static void main(String[] args) {
        new Thread(new exclusive_rs()).start();
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
