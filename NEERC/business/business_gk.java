import java.util.*;
import java.io.*;

class business_gk {
    static Scanner in;
    static PrintWriter out;
    
    void run() throws IOException {
        int n = in.nextInt();
        int m = in.nextInt();

        int min = Integer.MAX_VALUE;
        for (int i = 0; i < m; i++) {
            int u = in.nextInt();
            int d = in.nextInt();

            int x = d * n / (u + d) + 1;
            min = Math.min(min, (u + d) * x - d * n);
        }

        out.println(min);
    }

    public static void main(String[] args) throws Exception {        
        in = new Scanner(new File("business.in"));
        out = new PrintWriter("business.out");

        new business_gk().run();

        in.close();
        out.close();
    }
}
