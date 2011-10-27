import java.io.*;
import java.util.*;

public class funny_rs_tl implements Runnable {
    private BufferedReader in;
    private PrintWriter out;
    private int[][] w;
    private int[] cur;
    private boolean[][] mark;
    private int n, m;
    private Set<String> answer, originalWords;
    
    private void check(boolean expr, String msg) {
        if (!expr) {
            throw new Error(msg);
        }
    }
    
    private void checkBounds(int n, int low, int hi, String nStr) {
        check((low <= n) && (n <= hi), nStr + " is not in [" + low + ", " + hi + "]");
    }
    
    private void gen(int minWords, int pos) {
        if (pos == 26) {
            int good = 0;
            for (int i = 0; i < m; i++) {
                if (mark[pos][i]) {
                    good++;
                }
            }
            if (good > minWords) {
                return;
            }
            genWords("");
            return;
        }
        for (int u = 0; ; u++) {
            cur[pos] = u;
            int good = 0;
            for (int i = 0; i < m; i++) {
                mark[pos + 1][i] = mark[pos][i] && (w[i][pos] >= u);
                if (mark[pos + 1][i]) {
                    good++;
                }
            }
            if (good < minWords) {
                break;
            }
            gen(minWords, pos + 1);
            if (answer.size() == n) {
                break;
            }
        }
    }

    private void genWords(String prefix) {
        if (answer.size() == n) {
            return;
        }
        boolean found = false;
        for (int i = 0; i < 26; i++) {
            if (cur[i] > 0) {
                cur[i]--;
                genWords(prefix + (char) ('A' + i));
                cur[i]++;
                found = true;
            }
        }
        if (!found) {
            if (prefix.length() > 0 && !originalWords.contains(prefix)) {
                answer.add(prefix);
            }
        }
    }

    private void solve() throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());
        checkBounds(n, 1, 100, "n");
        checkBounds(m, 1, 1000, "m");
        w = new int[m][26];
        originalWords = new HashSet<String>();
        for (int i = 0; i < m; i++) {
            String line = in.readLine();
            originalWords.add(line);
            check(line.length() <= 100, "word length > 100");
            for (int j = 0; j < line.length(); j++) {
                int ch = line.charAt(j) - 'A';
                check((0 <= ch) && (ch < 26), "Invalid chars");
                w[i][ch]++;
            }
        }
        
        mark = new boolean[27][m];
        cur = new int[26];
        answer = new HashSet<String>();
        for (int i = m; i >= 0; i--) {
            if (answer.size() < n) {
                Arrays.fill(mark[0], true);
                gen(i, 0);
            }
        }
        for (String w: answer) {
            out.println(w);
        }
    }
    
    public static void main(String[] args) {
        new Thread(new funny_rs_tl()).start();
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
