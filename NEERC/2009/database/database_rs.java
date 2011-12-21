import java.io.*;
import java.util.*;

public class database_rs implements Runnable {
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
    
    private class Row implements Comparable<Row> {
        public int u, v;
        public int num;
        
        public int compareTo(Row that) {
            if (u != that.u) {
                return u - that.u;
            }
            if (v != that.v) {
                return v - that.v;
            }
            return num - that.num;
        }
        
        @Override
        public boolean equals(Object o) {
            Row that = (Row) o;
            return (u == that.u) && (v == that.v) && (num == that.num);
        }
    }
    
    private void solve() throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());
        checkBounds(n, 1, 10000, "n");
        checkBounds(m, 1, 10, "m");
        int[][] t = new int[n][m];
        Map<String, Integer> words = new HashMap<String, Integer>();
        int wordsCount = 0;
        for (int i = 0; i < n; i++) {
            String line = in.readLine();
            check(line.length() <= 80, "line too long");
            st = new StringTokenizer(line, ",");
            for (int j = 0; j < m; j++) {
                String word = st.nextToken();
                for (int u = 0; u < word.length(); u++) {
                    char ch = word.charAt(u);
                    check((' ' <= ch) && (ch <= '~'), "invalid symbol in word: " + ch);
                }
                check(word.charAt(0) != ' ', "leading spaces in word");
                check(word.charAt(word.length() - 1) != ' ', "trailing spaces in word");
                if (!words.containsKey(word)) {
                    words.put(word, wordsCount++);
                }
                t[i][j] = words.get(word);
            }
        }
        Row[] rows = new Row[n];
        for (int i = 0; i < n; i++) {
            rows[i] = new Row();
        }
        for (int u = 0; u < m; u++) {
            for (int v = u + 1; v < m; v++) {
                for (int i = 0; i < n; i++) {
                    rows[i].u = t[i][u];
                    rows[i].v = t[i][v];
                    rows[i].num = i + 1;
                }
                Arrays.sort(rows);
                for (int i = 0; i < n - 1; i++) {
                    if (rows[i].u == rows[i + 1].u && rows[i].v == rows[i + 1].v) {
                        out.println("NO");
                        out.println(rows[i].num + " " + rows[i + 1].num);
                        out.println((u + 1) + " " + (v + 1));
                        return;
                    }
                }
            }
        }
        out.println("YES");
    }
    
    public static void main(String[] args) {
        new Thread(new database_rs()).start();
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
