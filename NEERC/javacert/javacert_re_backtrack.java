import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2009 Problem J: Java Certification
 * This solution is slow (uses backtracking)
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class javacert_re_backtrack {

	public static void main(String[] args) throws Exception {
		new javacert_re_backtrack().go();
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
	Pair[] cursol;
	Pair[] sol;
	int soldiff;

	void solve() {
		buildPairs();
		sortPairs();
		w = n - k;
		cursol = new Pair[m];
		soldiff = Integer.MAX_VALUE;
		find(0, 0, 0, Integer.MAX_VALUE, Integer.MIN_VALUE);
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

	private void sortPairs() {
		final double mid = n / m;
		for (int i = 0; i < m; i++) {
		    Collections.sort(llp.get(i), new Comparator<Pair>() {
			    public int compare(Pair p1, Pair p2) {
				    double d1 = Math.abs(p1.ni - mid);
				    double d2 = Math.abs(p2.ni - mid);
				    return Double.compare(d1, d2);
			    }
		    });
		}
	}

	void find(int i, int ws, int ns, int minni, int maxni) {
		if (ns > n || ws > w)
			return;
		int diff = maxni - minni;
		if (diff >= soldiff)
			return;
		if (i == m) {
			if (ns < n || ws < w)
				return;
			soldiff = diff;
			sol = cursol.clone();
			return;
		}
		for (Pair p : llp.get(i)) {
			cursol[i] = p;
			find(i + 1, ws + p.wi, ns + p.ni, Math.min(minni, p.ni), Math.max(maxni, p.ni));
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
