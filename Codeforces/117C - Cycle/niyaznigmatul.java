// This is Nigmatullin's code. But shouldn't this time out? It's O(n^3)

import java.io.*;
import java.util.*;
import java.math.*;

public class niyaznigmatul implements Runnable {

    void solve() throws Exception {
        int n = nextInt();
        char[][] c = new char[n][];
        for (int i = 0; i < n; i++) {
            c[i] = sc.nextToken().toCharArray();
        }

        int[] count = new int[n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (c[i][j] == '1') {
                    count[i]++;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (c[i][j] == '1') {
                    if (count[j] >= count[i]) {
                        for (int k = 0; k < n; k++) {
                            if (k == i || k == j) {
                                continue;
                            }
                            if (c[j][k] == '1' && c[k][i] == '1') {
                                out.println((1 + i) + " " + (1 + j) + " "
                                    + (1 + k));
                                return;
                            }
                        }
                        throw new Exception("You shouldn't be here.");
                    }
                }
            }
        }
        out.println(-1);
    }

    FastScanner sc;
    PrintWriter out;

    public void run() {
        Locale.setDefault(Locale.US);
        try {
            sc = new FastScanner(System.in);
            out = new PrintWriter(System.out);
            solve();
            sc.close();
            out.close();
        } catch (Throwable e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    int nextInt() {
        return sc.nextInt();
    }

    String nextToken() {
        return sc.nextToken();
    }

    long nextLong() {
        return sc.nextLong();
    }

    double nextDouble() {
        return sc.nextDouble();
    }

    BigInteger nextBigInteger() {
        return sc.nextBigInteger();
    }

    class FastScanner extends BufferedReader {
        StringTokenizer st;
        boolean eof;
        String buf;
        String curLine;
        boolean createST;

        public FastScanner(String fileName) throws FileNotFoundException {
            this(fileName, true);
        }

        public FastScanner(String fileName, boolean createST)
        throws FileNotFoundException {
            super(new FileReader(fileName));
            this.createST = createST;
            nextToken();
        }

        public FastScanner(InputStream stream) {
            this(stream, true);
        }

        public FastScanner(InputStream stream, boolean createST) {
            super(new InputStreamReader(stream));
            this.createST = createST;
            nextToken();
        }

        String nextLine() {
            String ret = curLine;
            if (createST) {
                st = null;
            }
            nextToken();
            return ret;
        }

        String nextToken() {
            if (!createST) {
                try {
                    curLine = readLine();
                } catch (Exception e) {
                    eof = true;
                }
                return null;
            }
            while (st == null || !st.hasMoreTokens()) {
                try {
                    curLine = readLine();
                    st = new StringTokenizer(curLine);
                } catch (Exception e) {
                    eof = true;
                    break;
                }
            }
            String ret = buf;
            buf = eof ? "-1" : st.nextToken();
            return ret;
        }

        int nextInt() {
            return Integer.parseInt(nextToken());
        }

        long nextLong() {
            return Long.parseLong(nextToken());
        }

        double nextDouble() {
            return Double.parseDouble(nextToken());
        }

        BigInteger nextBigInteger() {
            return new BigInteger(nextToken());
        }

        public void close() {
            try {
                buf = null;
                st = null;
                curLine = null;
                super.close();
            } catch (Exception e) {

            }
        }

        boolean isEOF() {
            return eof;
        }
    }

    public static void main(String[] args) {
        new niyaznigmatul().run();
    }
}