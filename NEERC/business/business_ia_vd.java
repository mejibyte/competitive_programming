import java.io.*;
import java.util.Scanner;

/**
 * @author Iskander Akishev
 * @author Vladimir Danilov
 */
public class business_ia_vd implements Runnable {

	private static final String FILE_NAME = "business";

	public void run() {
		try {
			solve();
		} catch (Throwable t) {
			t.printStackTrace();
			System.exit(1);
		}
	}

	private Scanner in;
	private PrintWriter out;

	private void solve() throws Exception {
		in = new Scanner(new FileReader(FILE_NAME + ".in"));
		out = new PrintWriter(new File(FILE_NAME + ".out"));

		try {
			int n = in.nextInt();
			int m = in.nextInt();

			int res = 1000000000;
			for (int i = 0; i < m; i++) {
				int u = in.nextInt();
				int d = in.nextInt();

				int upOnly = u * n;
				int mod = upOnly % (u + d);
				res = Math.min(res, mod == 0 ? u + d : mod);
			}
			
			out.print(res);
		} finally {
			in.close();
			out.close();
		}
	}

	public static void main(String[] args) {
		new Thread(new business_ia_vd()).start();
	}
}