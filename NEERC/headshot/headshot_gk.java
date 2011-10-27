import java.util.*;
import java.io.*;

public class headshot_gk {
    static Scanner in;
    static PrintWriter out;

    public void run() throws IOException {
        char[] a = in.next().toCharArray();
        char prev = a[a.length - 1];
        int load = 0;
        int load2 = 0;
        for (char i : a) {
            if (i == '1') {
                load++;
                if (prev == '1') {
                    load2++;
                }
            }
            prev = i;
        }
        int z = load2 * a.length - load * load;
        out.println(z == 0 ? "EQUAL" : z < 0 ? "ROTATE" : "SHOOT");
    }

    public static void main(String[] args) throws Exception {        
        in = new Scanner(new File("headshot.in"));
        out = new PrintWriter("headshot.out");

        new headshot_gk().run();

        in.close();
        out.close();
    }
}
