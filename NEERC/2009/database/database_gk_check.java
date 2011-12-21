import java.util.*;
import java.io.*;

public class database_gk_check implements Runnable {
    static final int MAX_N = 10000;
    static final int MAX_M = 100;
    static final int MAX_W = 80;
    static final int MIN_CH = 32;
    static final int MAX_CH = 126;

    static Scanner in;
    static PrintWriter out;

    public void run() {
        int n = in.nextInt();
        int m = in.nextInt();
        in.nextLine();

        assert 1 <= n && n <= MAX_N;
        assert 1 <= m && m <= MAX_M;
        
        String[][] values = new String[n][];
        for (int i = 0; i < n; i++) {
            String line = in.nextLine();
            assert line.length() <= MAX_W;
            for (char ch : line.toCharArray()) {
                assert MIN_CH <= ch && ch <= MAX_CH;
            }
            values[i] =  line.split(",");
            for (String value : values[i]) {
                assert value.length() > 0;
                assert value.charAt(0) != ' ';
                assert value.charAt(value.length() - 1) != ' ';
            }
            assert values[i].length == m;
        }
        assert !in.hasNext();
        
        for (int c1 = 0; c1 < m; c1++) {
            for (int c2 = c1 + 1; c2 < m; c2++) {
                Map<String, Integer> map = new HashMap<String, Integer>();
                for (int r1 = 0; r1 < n; r1++) {
                    Integer r2 = map.put(values[r1][c1] + "," + values[r1][c2], r1);
                    if (r2 != null) {
                        out.println("NO");
                        out.println((r2 + 1) + " "  + (r1 + 1));
                        out.println((c1 + 1) + " "  + (c2 + 1));
                        return;
                    }
                }
            }
        }
        out.println("YES");
    }

    public static void main(String[] args) throws Exception {        
        in = new Scanner(new File("database.in"));
        out = new PrintWriter("database.out");

        new database_gk_check().run();

        in.close();
        out.close();
    }
}
