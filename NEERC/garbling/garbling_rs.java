import java.io.*;
import java.util.*;
import java.math.BigInteger;

public class garbling_rs implements Runnable {
    private BufferedReader in;
    private PrintWriter out;
    
    private void check(boolean expr, String msg) {
        if (!expr) {
            throw new Error(msg);
        }
    }
    
    private void checkBounds(long n, long low, long hi, String nStr) {
        check((low <= n) && (n <= hi), nStr + " is not in [" + low + ", " + hi + "]");
    }
    
    private int r, c;
    private char[][] map;
    private int[] fTemp, fSingle;
    private int[] aTemp, aSingle;
    private static final int modulo = 100000;
    
    private void applySingle(int[] f, int[] a, int n) {
        int count = 0;
        for (int i = 0; i < r - 1; i++) {
            for (int j = 0; j < c - 1; j++) {
                if (count++ >= n) {
                    return;
                }
                int p11 = i * c + j;
                int p12 = p11 + 1;
                int p21 = p11 + c;
                int p22 = p11 + c + 1;
                
                a[f[p11]]++;
                while (a[f[p11]] >= modulo) {
                    a[f[p11]] -= modulo;
                }
                if (map[i][j] == 'L') {
                    int tmp = f[p11];
                    f[p11] = f[p12];
                    f[p12] = f[p22];
                    f[p22] = f[p21];
                    f[p21] = tmp;
                } else if (map[i][j] == 'R') {
                    int tmp = f[p11];
                    f[p11] = f[p21];
                    f[p21] = f[p22];
                    f[p22] = f[p12];
                    f[p12] = tmp;
                }
            }
        }
    }
    
    private void inversePerm(int[] f) {
        for (int i = 0; i < f.length; i++) {
            fTemp[f[i]] = i;
        }
        System.arraycopy(fTemp, 0, f, 0, f.length);
    }
    
    private void apply(BigInteger n, int[] f, int[] a) {
        if (n.equals(BigInteger.ZERO)) {
            for (int i = 0; i < f.length; i++) {
                f[i] = i;
                a[i] = 0;
            }
            return;
        }
        apply(n.shiftRight(1), f, a);
        for (int i = 0; i < f.length; i++) {
            fTemp[i] = f[f[i]];
            aTemp[i] = a[i] + a[f[i]];
            if (aTemp[i] >= modulo) {
                aTemp[i] -= modulo;
            }
        }
        System.arraycopy(fTemp, 0, f, 0, f.length);
        System.arraycopy(aTemp, 0, a, 0, a.length);
        if (n.testBit(0)) {
            for (int i = 0; i < f.length; i++) {
                fTemp[i] = f[fSingle[i]];
                aTemp[i] = aSingle[i] + a[fSingle[i]];
                if (aTemp[i] >= modulo) {
                    aTemp[i] -= modulo;
                }
            }
            System.arraycopy(fTemp, 0, f, 0, f.length);
            System.arraycopy(aTemp, 0, a, 0, a.length);
        }
    }
    
    private void solve() throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        r = Integer.parseInt(st.nextToken());
        c = Integer.parseInt(st.nextToken());
        BigInteger n = new BigInteger(st.nextToken());
        checkBounds(r, 2, 300, "r");
        checkBounds(c, 2, 300, "c");
        check(n.compareTo(BigInteger.ZERO) >= 0, "n is negative");
        check(n.compareTo(BigInteger.TEN.pow(100)) < 0, "n is greater than 10^{100}");
        map = new char[r - 1][];
        for (int i = 0; i < r - 1; i++) {
            String line = in.readLine();
            check(line.length() == c - 1, "Invalid size of map");
            map[i] = line.toCharArray();
            for (int j = 0; j < c - 1; j++) {
                check(map[i][j] == 'L' || map[i][j] == 'R' || map[i][j] == 'N', "invalid character in map");
            }
        }
        
        fTemp = new int[r * c];
        aTemp = new int[r * c];
        int[] f = new int[r * c];
        int[] a = new int[r * c];
        int block = (r - 1) * (c - 1);

        fSingle = new int[r * c];
        aSingle = new int[r * c];
        for (int i = 0; i < f.length; i++) {
            fSingle[i] = i;
            aSingle[i] = 0;
        }
        applySingle(fSingle, aSingle, block);
        inversePerm(fSingle);

        apply(n.divide(BigInteger.valueOf(block)), f, a);
        inversePerm(f);
        applySingle(f, a, n.mod(BigInteger.valueOf(block)).intValue());
        for (int i = 0; i < f.length; i++) {
            out.println(a[i]);
        }
    }
    
    public static void main(String[] args) {
        new Thread(new garbling_rs()).start();
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
