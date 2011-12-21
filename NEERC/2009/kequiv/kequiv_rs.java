import java.io.*;
import java.util.*;

public class kequiv_rs implements Runnable {
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
    
    private long[] a, b;
    private long[] ten;
    private long[] x, y;
    private long[] intersect1X, intersect1Y;  
    private long[] intersect2X, intersect2Y;  
    private int n, m;

    private long[][] aTen, bTen;
    
    private boolean examine(int d1, int d2, int k, long a, long b) {
        long x1 = d1 * ten[k - 1];
        long y1 = (d1 + 1) * ten[k - 1] - 1;
        
        long x2 = d2 * ten[k - 1];
        long y2 = (d2 + 1) * ten[k - 1] - 1;
        
        boolean contains1 = (a <= x1 && y1 <= b);
        boolean contains2 = (a <= x2 && y2 <= b);
        boolean intersects1 = !(b < x1 || a > y1); 
        boolean intersects2 = !(b < x2 || a > y2);
        
        if (intersects1 && !contains1) {
            return false;
        }
        if (intersects2 && !contains2) {
            return false;
        }
        
        return contains1 == contains2;
    }
    
    private boolean testEQ(int d1, int d2) {
        for (int k = 1; k <= 18; k++) {
            m = 0;
            for (int i = 0; i < n; i++) {
                long left = aTen[k][i];
                long right = bTen[k][i];
                if (left < right) {
                    x[m] = a[i];
                    y[m] = left * ten[k] + ten[k] - 1;
                    m++;
                    
                    x[m] = right * ten[k];
                    y[m] = b[i];
                    m++;
                } else {
                    x[m] = a[i];
                    y[m] = b[i];
                    m++;
                }
            }
            long x1 = d1 * ten[k - 1];
            long y1 = (d1 + 1) * ten[k - 1] - 1;
            
            long x2 = d2 * ten[k - 1];
            long y2 = (d2 + 1) * ten[k - 1] - 1;
            for (int i = 0; i < m; i++) {
                long curLeft = x[i] - x[i] % ten[k];
                long curRight = curLeft + ten[k] - 1;
                int hi = m - 1;
                for (int j = i; j < m; j++) {
                    if (x[j] > curRight) {
                        hi = j - 1;
                        break;
                    }
                }
                
                int count1 = 0;
                int count2 = 0;
                for (int j = i; j <= hi; j++) {
                    long from = x[j] % ten[k];
                    long to = y[j] % ten[k];
                    
                    long f1 = Math.max(from, x1);
                    long t1 = Math.min(to, y1);
                    if (f1 <= t1) {
                        intersect1X[count1] = f1 - x1;
                        intersect1Y[count1++] = t1 - x1;
                    }
                    long f2 = Math.max(from, x2);
                    long t2 = Math.min(to, y2);
                    if (f2 <= t2) {
                        intersect2X[count2] = f2 - x2;
                        intersect2Y[count2++] = t2 - x2;
                    }
                }
                
                if (count1 != count2) {
                    return false;
                }
                for (int j = 0; j < count1; j++) {
                    if (intersect1X[j] != intersect2X[j]) {
                        return false;
                    }
                    if (intersect1Y[j] != intersect2Y[j]) {
                        return false;
                    }
                }
                
                i = hi;
            }
        }
        return true;
    }

    private void solve() throws IOException {
        n = Integer.parseInt(in.readLine());
        checkBounds(n, 1, 10000, "n");
        a = new long[n];
        b = new long[n];
        for (int i = 0; i < n; i++) {
            StringTokenizer st = new StringTokenizer(in.readLine());
            a[i] = Long.parseLong(st.nextToken());
            b[i] = Long.parseLong(st.nextToken());
            check((1 <= a[i]) && (a[i] <= b[i]) && (b[i] <= 1000000000000000000L), "invalid interval");
        }
        for (int i = 0; i + 1 < n; i++) {
            check(b[i] + 2 <= a[i + 1], "touching or overlaping intervals");
        }
        
        ten = new long[19];
        ten[0] = 1;
        for (int i = 1; i < ten.length; i++) {
            ten[i] = 10 * ten[i - 1];
        }

        aTen = new long[19][n];
        bTen = new long[19][n];
        for (int k = 0; k <= 18; k++) {
            for (int i = 0; i < n; i++) {
                aTen[k][i] = a[i] / ten[k];
                bTen[k][i] = b[i] / ten[k];
            }
        }
        
        x = new long[2 * n];
        y = new long[2 * n];
        intersect1X = new long[2 * n];
        intersect1Y = new long[2 * n];
        intersect2X = new long[2 * n];
        intersect2Y = new long[2 * n];
        
        testEQ(4, 5);
        
        boolean[][] eq = new boolean[10][10];
        for (int u = 1; u < 10; u++) {
            eq[u][u] = true;
            for (int v = u + 1; v < 10; v++) {
                if ((b[n - 1] == ten[18]) && (u == 1)) {
                    eq[u][v] = false;
                    continue;
                }
                eq[u][v] = testEQ(u, v);
            }
        }
        
        boolean[] mark = new boolean[10];
        for (int i = 1; i < 10; i++) {
            if (mark[i]) {
                continue;
            }
            for (int j = i; j < 10; j++) {
                if (eq[i][j]) {
                    mark[j] = true;
                    out.print(j);
                }
            }
            out.println();
        }
    }
    
    public static void main(String[] args) {
        new Thread(new kequiv_rs()).start();
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
