import java.io.*;
import java.util.Scanner;

public class business_mb implements Runnable {
    public static void main(String[] args) {
        new Thread(new business_mb()).start();
    }

    public void run() {
        try {
            final Scanner in = new Scanner(new FileReader("business.in"));
            final PrintWriter out = new PrintWriter("business.out");

            final int n = in.nextInt();
            final int m = in.nextInt();

            int ans = Integer.MAX_VALUE;
            for (int i = 0; i < m; i++) {
                final int u = in.nextInt();
                final int d = in.nextInt();
                final int x = (n * d) / (u + d) + 1;
                final int cur = x * (u + d) - n * d;
                ans = Math.min(ans, cur);
            }

            out.println(ans);

            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
