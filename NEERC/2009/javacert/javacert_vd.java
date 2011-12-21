import java.io.*;
import java.util.Arrays;
import java.util.Scanner;

/**
 * @author Vladimir Danilov
 */
public class javacert_vd implements Runnable {

	private static final String FILE_NAME = "javacert";
	private static final int MAX_VALUE = Integer.MAX_VALUE / 2;

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

		int[][] rev = new int[101][101];

		for (int i = 0; i <= 100; i++) {
			for (int j = 0; j <= 100; j++) {
				rev[i][j] = errorCount(i, j);
			}
		}

		int k = in.nextInt();
		int n = in.nextInt();
		int m = in.nextInt();

		int [] perc = new int[n];
		for (int i = 0; i < m; i++) {
			perc[i] = in.nextInt();
		}

		int err = n - k;

		int result = MAX_VALUE;

		int [] resCount = new int[m];
		int [] resErrors = new int[m];

		for (int min = 1; min <= n / m; min++) {
			int[][][] d = new int[m + 1][n + 1][n + 1];
			for (int[][] r : d) {
				for (int[] c : r) {
					Arrays.fill(c, MAX_VALUE);
				}
			}

			int [][][] candCount = new int[m + 1][n + 1][n + 1];
			int [][][] candErrors = new int[m + 1][n + 1][n + 1];

			d[0][0][0] = 0;

			for (int i = 0; i < m; i++) {
				for (int processed = min * i; processed <= n; processed++) {
					for (int errors = 0; errors <= processed; errors++) {
						if (d[i][processed][errors] == MAX_VALUE) {
							continue;
						}
						int max = n - processed;
						for (int count = min; count <= max; count++) {
							int newCount = processed + count;
							int add = rev[perc[i]][count];
							if (add != -1) {
								int newErrors = errors + add;
								int cand = Math.max(d[i][processed][errors], count);
								if (cand < d[i + 1][newCount][newErrors]) {
									d[i + 1][newCount][newErrors] = cand;
									candCount[i + 1][newCount][newErrors] = count;
									candErrors[i + 1][newCount][newErrors] = add;
								}
							}
						}
					}
				}
			}

			if (d[m][n][err] != MAX_VALUE && result > d[m][n][err] - min) {
				int curCount = n;
				int curErrors = err;
				for (int i = m; i > 0; i--) {
					resCount[i - 1] = candCount[i][curCount][curErrors];
					resErrors[i - 1] = candErrors[i][curCount][curErrors];

					curCount -= resCount[i - 1];
					curErrors -= resErrors[i - 1];
				}

				result = d[m][n][err] - min;
			}
		}
		
		for (int i = 0; i < m; i++) {
			out.printf("%d %d\n", resErrors[i], resCount[i]);
		}

		in.close();
		out.close();
	}

	private int errorCount(int percentage, int questionCount) {
		int right = Math.max((percentage * questionCount) / 100, 0);
		while (true) {
			long resP = countPercentage(questionCount, right);
			if (resP == percentage) {
				return questionCount - right;
			}
			if (resP > percentage) {
				return -1;
			}
			right++;
		}
	}

	private long countPercentage(int questionCount, int right) {
		if (questionCount > 0 && (right * 200) % questionCount == 0) {
			int floor = (right * 100) / questionCount;
			if ((right * 100) % questionCount == 0) {
				return floor;
			}
			return floor + (floor % 2);
		}
		double a = (100.0 * right / questionCount);
		return Math.round(a);
	}

	public static void main(String[] args) {
		new Thread(new javacert_vd()).start();
	}
}