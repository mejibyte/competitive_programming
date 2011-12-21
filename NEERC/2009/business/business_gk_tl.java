/* O(n * m) */
import java.util.*;
import java.io.*;

class business_gk_tl {
    static Scanner in;
    static PrintWriter out;
    
    void run() throws IOException {
        int n = in.nextInt();
        int m = in.nextInt();

        int min = Integer.MAX_VALUE;
        for (int i = 0; i < m; i++) {
            int u = in.nextInt();
            int d = in.nextInt();

            for (int j = 0; j <= n; j++) {
                int f = u * j - d * (n - j);
                if (f > 0) {
                    min = Math.min(min, f);
                }
            }
        }

        out.println(min);
    }

    public static void main(String[] args) throws Exception {        
        in = new Scanner(new File("business.in"));
        out = new PrintWriter("business.out");

        new business_gk_tl().run();

        in.close();
        out.close();
    }
}
