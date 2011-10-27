import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2009 Problem J: Java Certification
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class javacert_re {

	public static void main(String[] args) throws Exception {
		new javacert_re().go();
	}

	void go() throws Exception {
		read();
		solve();
		write();
	}

	int k;
	int n;
	int m;
	int[] p;

	void read() throws Exception {
		Scanner in = new Scanner(new File("javacert.in"));
		in.useLocale(Locale.US);
		k = in.nextInt();
		n = in.nextInt();
		m = in.nextInt();
		in.nextLine();
		assert k >= 0 && k <= n;
		assert n >= 1 && n <= 100;
		assert m >= 1 && m <= 10;
		p = new int[m];
		for (int i = 0; i < m; i++) {
		    p[i] = in.nextInt();
			in.nextLine();
			assert p[i] >= 0 && p[i] <= 100;
		}
		in.close();
	}

	static class Pair {
		int wi;
		int ni;

		Pair(int wi, int ni) {
			this.wi = wi;
			this.ni = ni;
		}

		@Override
		public String toString() {
			return wi + " " + ni + " " + (100.0*(ni - wi) / ni);
		}
	}

	int w;
	List<List<Pair>> llp;
	int[][][] dp;
	Pair[][][] lp;

	int bestdiff = Integer.MAX_VALUE;
	Pair[] sol;

	void solve() {
		buildPairs();
		w = n - k;
		dp = new int[m + 1][w + 1][n + 1];
		lp = new Pair[m + 1][w + 1][n + 1];
		for (int minni = 0; minni <= n; minni++) {
		    for (int i = 0; i <= m; i++) {
		        for (int wi = 0; wi <= w; wi++) {
			        Arrays.fill(dp[i][wi], Integer.MAX_VALUE);
			        Arrays.fill(lp[i][wi], null);
		        }
		    }
			dp[0][0][0] = minni;
			for (int i = 0; i < m; i++) {
				for (Pair p : llp.get(i))
					if (p.ni >= minni)
						for (int ni = 0; ni <= n; ni++) {
							int nj = ni + p.ni;
							if (nj <= n)
								for (int wi = 0; wi <= w; wi++) {
									int wj = wi + p.wi;
									if (wj <= w)
										if (dp[i][wi][ni] < Integer.MAX_VALUE) {
											int maxni = Math.max(dp[i][wi][ni], p.ni);
											if (maxni < dp[i + 1][wj][nj]) {
												dp[i + 1][wj][nj] = maxni;
												lp[i + 1][wj][nj] = p;
											}
										}
								}
			            }
			}
			int maxni = dp[m][w][n];
			if (maxni == Integer.MAX_VALUE)
				continue;
			int diff = maxni - minni;
			if (diff < bestdiff) {
				sol = new Pair[m];
				int ws = w;
				int ns = n;
				for (int i = m; --i >= 0;) {
				    sol[i] = lp[i + 1][ws][ns];
					ws -= sol[i].wi;
					ns -= sol[i].ni;
				}
				assert ns == 0;
				assert ws == 0;
				bestdiff = diff;
			}
		}
	}

	private void buildPairs() {
		llp = new ArrayList<List<Pair>>();
		for (int i = 0; i < m; i++) {
			llp.add(new ArrayList<Pair>());
		}
		for (int ni = 1; ni <= n; ni++) {
			for (int wi = 0; wi <= ni; wi++) {
				int ppp = 100 * (ni - wi);
				int pp = (2 * ppp + ni) / (2 * ni);
				if (2 * ppp % ni == 0 && 2 * ppp / ni % 2 == 1 && pp % 2 == 1)
					pp--;
				for (int i = 0; i < m; i++) {
				    if (p[i] == pp)
					    llp.get(i).add(new Pair(wi, ni));
				}
			}
		}
	}

	void write() throws Exception {
		PrintWriter out = new PrintWriter("javacert.out");
		for (int i = 0; i < m; i++) {
		    out.printf("%d %d%n", sol[i].wi,  sol[i].ni);
		}
		out.close();
	}

//----------------- just for validation ------------------

	/**
	 * Strict scanner to veryfy 100% correspondence between input files and input file format specification.
	 * It is a drop-in replacement for {@link java.util.Scanner} that could be added to a soulution source
	 * (cut-and-paste) without breaking its ability to work with {@link java.util.Scanner}.
	 */
	public class Scanner {
		private final BufferedReader in;
		private String line = "";
		private int pos;
		private int lineNo;
		private boolean localeset;

		public Scanner(File source) throws FileNotFoundException {
			in = new BufferedReader(new FileReader(source));
			nextLine();
		}

		public void close() {
			assert line == null : "Extra data at the end of file";
			try {
				in.close();
			} catch (IOException e) {
				throw new AssertionError("Failed to close with " + e);
			}
		}

		public void nextLine() {
			assert line != null : "EOF";
			assert pos == line.length() : "Extra characters on line " + lineNo;
			try {
				line = in.readLine();
			} catch (IOException e) {
				throw new AssertionError("Failed to read line with " + e);
			}
			pos = 0;
			lineNo++;
		}

		public String next() {
			assert line != null : "EOF";
			assert line.length() > 0 : "Empty line " + lineNo;
			if (pos == 0)
				assert line.charAt(0) > ' ' : "Line " + lineNo + " starts with whitespace";
			else {
				assert pos < line.length() : "Line " + lineNo + " is over";
				assert line.charAt(pos) == ' ' : "Wrong whitespace on line " + lineNo;
				pos++;
				assert pos < line.length() : "Line " + lineNo + " is over";
				assert line.charAt(0) > ' ' : "Line " + lineNo + " has double whitespace";
			}
			StringBuilder sb = new StringBuilder();
			while (pos < line.length() && line.charAt(pos) > ' ')
				sb.append(line.charAt(pos++));
			return sb.toString();
		}

		public int nextInt() {
			String s = next();
			assert s.length() == 1 || s.charAt(0) != '0' : "Extra leading zero in number " + s + " on line " + lineNo;
			assert s.charAt(0) != '+' : "Extra leading '+' in number " + s + " on line " + lineNo;
			try {
				return Integer.parseInt(s);
			} catch (NumberFormatException e) {
				throw new AssertionError("Malformed number " + s + " on line " + lineNo);
			}
		}

		public double nextDouble() {
			assert localeset : "Locale must be set with useLocale(Locale.US)";
			String s = next();
			assert s.length() == 1 || s.startsWith("0.") || s.charAt(0) != '0' : "Extra leading zero in number " + s + " on line " + lineNo;
			assert s.charAt(0) != '+' : "Extra leading '+' in number " + s + " on line " + lineNo;
			try {
				return Double.parseDouble(s);
			} catch (NumberFormatException e) {
				throw new AssertionError("Malformed number " + s + " on line " + lineNo);
			}
		}

		public void useLocale(Locale locale) {
			assert locale == Locale.US;
			localeset = true;
		}
	}
}