import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2009 Problem B: Business Center 
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class business_re {

	public static void main(String[] args) throws Exception {
		new business_re().go();
	}

	void go() throws Exception {
		read();
		solve();
		write();
	}

	int n;
	int m;
	int[] u;
	int[] d;

	void read() throws Exception {
		Scanner in = new Scanner(new File("business.in"));
		in.useLocale(Locale.US);
		n = in.nextInt();
		m = in.nextInt();
		in.nextLine();
		assert n >= 1 && n <= 1000000;
		assert m >= 1 && m <= 2000;
		u = new int[m];
		d = new int[m];
		for (int i = 0; i < m; i++) {
		    u[i] = in.nextInt();
			d[i] = in.nextInt();
			in.nextLine();
			assert u[i] >= 1 && u[i] <= 1000;
			assert d[i] >= 1 && d[i] <= 1000;
		}
		in.close();
	}

	int lowest = Integer.MAX_VALUE;

	void solve() {
		for (int i = 0; i < m; i++) {
		    // min { a * u - (n - a) * d }
			//       a * (u + d) = n * d
			//       a = n * d / (u + d)
			int a = n * d[i] / (u[i] + d[i]) + 1;
			int res = a * u[i] - (n - a) * d[i];
			lowest = Math.min(lowest, res);
		}
	}

	void write() throws Exception {
		PrintWriter out = new PrintWriter("business.out");
		out.println(lowest);
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
