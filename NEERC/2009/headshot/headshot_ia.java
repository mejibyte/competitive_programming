import java.io.*;
import java.util.ArrayList;

/**
 * @author Iskander Akishev
 */
public class headshot_ia implements Runnable {

	private static final String FILE_NAME = "headshot";

	public void run() {
		try {
			solve();
		} catch (Throwable t) {
			t.printStackTrace();
			System.exit(1);
		}
	}

	private BufferedReader in;
	private PrintWriter out;

	private void solve() throws Exception {
		in = new BufferedReader(new FileReader(FILE_NAME + ".in"));
		out = new PrintWriter(new File(FILE_NAME + ".out"));

		ArrayList<Boolean> b = new ArrayList<Boolean>();
		int m = 0;
		for (char c : in.readLine().trim().toCharArray()) {
			b.add(c == '1');
			if (c == '1') {
				m++;
			}
		}
		int n = b.size();

		b.add(b.get(0));
		int k = 0;
		int l = 0;
		for (int i = 0; i < n; i++) {
			if (!b.get(i)) {
				k++;
				if (b.get(i + 1)) {
					l++;
				}
			}
		}

		int compare = m * k - l * n;
		if (compare > 0) {
			out.println("SHOOT");
		} else if (compare < 0) {
			out.println("ROTATE");
		} else {
			out.println("EQUAL");
		}

		in.close();
		out.close();
	}

	public static void main(String[] args) {
		new Thread(new headshot_ia()).start();
	}
}