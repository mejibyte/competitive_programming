import java.io.*;
import java.util.*;

public class javacert_rs implements Runnable {
	private static final int inf = Integer.MAX_VALUE / 3;
	private BufferedReader in;
	private PrintWriter out;
	
	private void check(boolean expr, String msg) {
		if (!expr) {
			throw new Error(msg);
		}
	}
	
	private void checkBounds(int n, int low, int hi, String nStr) {
		check((low <= n) && (n <= hi), nStr + " is not in [" + low + ", " + hi + "]");
	}
	
	private int n, m, k;
	private int[][] kValue;
	private int[][][] w, prev;
	
	private int round(int a, int b) {
		if (a % b == 0) {
			return a / b;
		}
		if ((2 * a) % b == 0) {
			int r = a / b;
			if (r % 2 == 1) {
				r++;
			}
			return r;
		}
		return (int) Math.round(1.0 * a / b);
	}
	
	private void solve() throws IOException {
		StringTokenizer st = new StringTokenizer(in.readLine());
		k = Integer.parseInt(st.nextToken());
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		checkBounds(k, 0, n, "k");
		checkBounds(n, 1, 100, "n");
		checkBounds(m, 1, 10, "m");
		
		int[] p = new int[m];
		for (int i = 0; i < m; i++) {
			p[i] = Integer.parseInt(in.readLine());
			checkBounds(p[i], 0, 100, "p[i]");
		}
		
		kValue = new int[m][n + 1]; 
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < m; j++) {
				kValue[j][i] = -1;
				for (int t = 0; t <= i; t++) {
					if (round(100 * t, i) == p[j]) {
						kValue[j][i] = t;
						break;
					}
				}
			}
		}
		
		w = new int[m + 1][n + 1][k + 1];
		prev = new int[m + 1][n + 1][k + 1];
		int answer = inf;
		int[] ansN = new int[m];
		int[] ansK = new int[m];
		for (int min = 1; min <= n / m; min++) {
			for (int step = 0; step <= m; step++) {
				for (int u = 0; u <= n; u++) {
					for (int v = 0; v <= k; v++) {
						w[step][u][v] = inf;
					}
				}
			}
			w[0][0][0] = min;
			for (int step = 0; step < m; step++) {
				for (int u = 0; u <= n; u++) {
					for (int v = 0; v <= k; v++) {
						if (w[step][u][v] == inf) {
							continue;
						}
						for (int t = min; u + t <= n; t++) {
							int tk = kValue[step][t];
							if (tk == -1 || v + tk > k) {
								continue;
							}
							if (Math.max(w[step][u][v], t) < w[step + 1][u + t][v + tk]) {
								w[step + 1][u + t][v + tk] = Math.max(w[step][u][v], t);
								prev[step + 1][u + t][v + tk] = t;
							}
						}
					}
				}
			}
			int max = w[m][n][k];
			if (max - min < answer) {
				answer = max - min;
				int u = n;
				int v = k;
				for (int step = m; step > 0; step--) {
					int t = prev[step][u][v];
					ansN[step - 1] = t;
					ansK[step - 1] = kValue[step - 1][t];
					u -= t;
					v -= kValue[step - 1][t];
				}
			}
		}
		for (int i = 0; i < m; i++) {
			out.println((ansN[i] - ansK[i]) + " " + ansN[i]);
		}
	}
	
	public static void main(String[] args) {
		new Thread(new javacert_rs()).start();
	}

	public void run() {
		String problem = getClass().getName().split("_")[0];
		try {
			in = new BufferedReader(new FileReader(new File(problem + ".in")));
			out = new PrintWriter(new File(problem + ".out"));
			solve();
			in.close();
			out.close();
		} catch (IOException e) {
			e.printStackTrace();
			System.exit(1);
		}
	}
}
