import java.util.*;
import java.io.FileNotFoundException;
import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;

/**
 * @author Denis Kuznetsov
 */
public class headshot_dk {

	public static void main(String[] args) throws IOException {
		new headshot_dk().go();
	}

	void go() throws IOException {
		Scanner in = new Scanner(new File("headshot.in"));
        ArrayList<Integer> shots = new ArrayList<Integer>();

        int n = 0;
        int blanks = 0;
        while (in.hasNextInt()) {
            int shot = in.nextInt();
            shots.add(shot);
            n++;
            if (shot == 0) {
                blanks ++;
            }
        }

        int twoBlanksInRow = 0;
        //Copy first element to the end, so it is easier to calculate # of "0 0" subsequence
        shots.add(shots.get(0));
        for (int i = 0; i < shots.size() - 1; i++) {
            if (shots.get(i) == 0) {
                if (shots.get(i + 1) == 0) {
                    twoBlanksInRow ++;
                }
            }

        }
        // chance if rotate = # of blanks / # of shots.
        // chance if shot = # of two blanks in row / # of blanks.

        int diff = blanks * blanks - twoBlanksInRow * n;
        PrintWriter out = new PrintWriter("headshot.out");
//        PrintWriter out = new PrintWriter(System.out);
        if (diff == 0) {
            out.println("EQUAL");
        } else if (diff > 0) {
            out.println("ROTATE");
        } else {
            out.println("SHOOT");
        }
        out.flush();
        out.close();
	}
}
