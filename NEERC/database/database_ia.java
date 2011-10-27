import java.io.*;
import java.util.*;

/**
 * @author Iskander Akishev
 */
public class database_ia implements Runnable {

	private static final String FILE_NAME = "database";

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

		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());

		String[][] rows = new String[n][m + 1];

		for (int i = 0; i < n; i++) {
			String[] r = in.readLine().split(",");
			System.arraycopy(r, 0, rows[i], 0, m);
			rows[i][m] = Integer.toString(i + 1);
		}

		boolean found = false;
		LOOP: for (int j = 0; j < m; j++) {
			for (int k = j + 1; k < m; k++) {
				final int jj = j;
				final int kk = k;
				Arrays.sort(rows, new Comparator<String[]>() {
					public int compare(String[] o1, String[] o2) {
						int res = o1[jj].compareTo(o2[jj]);
						if (res == 0) res = o1[kk].compareTo(o2[kk]); 
						return res;
					}
				});

				for (int i = 1; i < n; i++) {
					if (rows[i - 1][j].equals(rows[i][j]) &&
						rows[i - 1][k].equals(rows[i][k]))
					{
						found = true;
						out.println("NO");
						out.println(rows[i - 1][m] + " " + rows[i][m]);
						out.println((j + 1) + " " + (k + 1));
						break LOOP;
					}
				}
			}
		}

		if (!found) {
			out.println("YES");
		}

		in.close();
		out.close();
	}

	public static void main(String[] args) {
		new Thread(new database_ia()).start();
	}
}