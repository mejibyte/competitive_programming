import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2009 Problem K: K-Equivalence
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class kequiv_re {
	static final boolean DEBUG = false;

	public static void main(String[] args) throws Exception {
		new kequiv_re().go();
	}

	void go() throws Exception {
		read();
		solve();
		write();
	}

	int n;
	long[] a;
	long[] b;

	void read() throws Exception {
		Scanner in = new Scanner(new File("kequiv.in"));
		in.useLocale(Locale.US);
		n = in.nextInt();
		in.nextLine();
		assert n >= 1 && n <= 10000;
		a = new long[n];
		b = new long[n];
		for (int i = 0; i < n; i++) {
			a[i] = in.nextLong();
			b[i] = in.nextLong();
			in.nextLine();
			assert a[i] >= 1 && a[i] <= b[i] && b[i] <= 1000000000000000000L;
			assert i == 0 || a[i] >= b[i - 1] + 2;
		}
		in.close();
	}


	long[] p10 = new long[19];
	long[] s = new long[1];
	int[] t = new int[1];
	int m;

	int cc;
	int[] cn = new int[11];

	void solve() {
		p10[0] = 1;
		for (int i = 1; i < p10.length; i++) {
		    p10[i] = p10[i - 1] * 10;
		}
		for (int i = 0; i < n; i++) {
			long a = this.a[i];
			long b = this.b[i] + 1;
			while (a < b) {
				int t = 0;
				while (t + 1 < p10.length && a + p10[t + 1] <= b && a % p10[t + 1] == 0)
					t++;
				append(a, t);
				a += p10[t];
			}
		}
		for (int p = 1; p < 10; p++) {
			if (cn[p] == 0) {
				cc++;
				mark(p);
			}
		}
	}

	void append(long s0, int t0) {
		int capacity = s.length;
		if (m >= capacity) {
			s = Arrays.copyOf(s, capacity * 2);
			t = Arrays.copyOf(t, capacity * 2);
		}
		s[m] = s0;
		t[m] = t0;
		m++;
		if (DEBUG)
			System.out.println(s0 + " - " + (s0 + p10[t0] - 1));
	}

	void mark(int p) {
		cn[p] = cc;
		for (int q = 1; q < 10; q++) {
			if (cn[q] == 0 && equiv(p, q))
				mark(q);
		}
	}

	private boolean equiv(int p, int q) {
		for (int i = 0; i < m; i++) {
			long s = this.s[i];
			int t = this.t[i];
			for (int u = t; u <= 18; u++) {
			    if (p10[u] > s)
				    break;
		        int d = (int)(s / p10[u] % 10);
				long ss = s;
				if (d == p)
					ss += p10[u] * (q - p);
				else if (d == q)
					ss += p10[u] * (p - q);
				else
					continue;
				if (u == 18)
					return false; // any shift by multiple of 10^18 is always out of range
				int j = Arrays.binarySearch(a, 0, n, ss);
				if (j < 0)
					j = -j - 2;
				if (j < 0 || j >= n || ss + p10[t] - 1 > b[j])
					return false; // out of range
		    }
		}
		return true;
	}

	void write() throws Exception {
		PrintWriter out = new PrintWriter("kequiv.out");
		boolean[] w = new boolean[11];
		for (int p = 1; p < 10; p++) {
			if (!w[p]) {
				for (int q = p; q < 10; q++) {
					if (cn[q] == cn[p]) {
						w[q] = true;
						out.print(q);
					}
				}
				out.println();
			}
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

		public long nextLong() {
			String s = next();
			assert s.length() == 1 || s.charAt(0) != '0' : "Extra leading zero in number " + s + " on line " + lineNo;
			assert s.charAt(0) != '+' : "Extra leading '+' in number " + s + " on line " + lineNo;
			try {
				return Long.parseLong(s);
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
