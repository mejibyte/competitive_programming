import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Scanner;

public class database_mb implements Runnable {
    private Scanner in;
    private PrintWriter out;

    public static void main(String[] args) {
        new Thread(new database_mb()).start();
    }

    public void run() {
        try {
            in = new Scanner(new FileReader("database.in"));
            out = new PrintWriter("database.out");

            solve();

            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void solve() {
        final int n = in.nextInt();
        final int m = in.nextInt();
        in.nextLine();

        String[][] table = new String[n][];
        for (int i = 0; i < n; i++) {
            table[i] =  in.nextLine().split(",");
        }

        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) {
                final HashMap<String, Integer> map = new HashMap<String, Integer>();
                for (int k = 0; k < n; k++) {
                    String key = table[k][i] + "," + table[k][j];
                    if (map.containsKey(key)) {
                        out.println("NO");
                        out.printf("%d %d\n", map.get(key) + 1, k + 1);
                        out.printf("%d %d\n", i + 1, j + 1);
                        return;
                    }
                    map.put(key, k);
                }
            }
        }

        out.println("YES");
    }
}
