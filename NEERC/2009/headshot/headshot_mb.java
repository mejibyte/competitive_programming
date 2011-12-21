import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class headshot_mb implements Runnable {
    private Scanner in;
    private PrintWriter out;

    public static void main(String[] args) {
        new Thread(new headshot_mb()).start();
    }

    public void run() {
        try {
            in = new Scanner(new FileReader("headshot.in"));
            out = new PrintWriter("headshot.out");

            solve();

            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void solve() {
        final ArrayList<Integer> chambers = new ArrayList<Integer>();
        int numLoaded = 0;
        int total = 0;
        final String line = in.nextLine();
        for (int i = 0; i < line.length(); i++) {
            final int chamber = line.charAt(i) - '0';
            if (chamber == 1) {
                numLoaded++;
            }
            chambers.add(chamber);
            total++;
        }


        final int numEmpty = total - numLoaded;
        int numLoadedAfterEmpty = 0;
        for (int i = 0; i < chambers.size(); i++) {
            if (chambers.get(i) == 0 && chambers.get((i + 1) % chambers.size()) == 1) {
                numLoadedAfterEmpty++;
            }
        }

        final double probRotate = (double) numLoaded / total;
        final double probShoot = (double) numLoadedAfterEmpty / numEmpty;

        if (Math.abs(probRotate - probShoot) < 1e-6) {
            out.println("EQUAL");
        } else if (probRotate < probShoot) {
            out.println("ROTATE");
        } else {
            out.println("SHOOT");
        }
    }
}
