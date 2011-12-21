import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2009 Problem D: Database
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class database_re {

	public static void main(String[] args) throws Exception {
		new database_re().go();
	}

	void go() throws Exception {
		read();
		solve();
		write();
	}

	int n;
	int m;
	List<List<String>> rows = new ArrayList<List<String>>();

	void read() throws Exception {
		Scanner in = new Scanner(new File("database.in"));
		in.useLocale(Locale.US);
		n = in.nextInt();
		m = in.nextInt();
		String rest = in.nextLine();
		assert rest.equals("");
		assert n >= 1 && n <= 10000;
		assert m >= 1 && m <= 10;
		for (int i = 0; i < n; i++) {
			String line = in.nextLine();
			assert line.length() <= 80;
			List<String> row = Arrays.asList(line.split(","));
			assert row.size() == m;
			for (int j = 0; j < m; j++) {
				String s = row.get(j);
				assert s.trim().equals(s);
				assert s.length() > 0;
				for (int k = 0; k < s.length(); k++) {
					char c = s.charAt(k);
					assert c >= 32 && c <= 126 && c != 44;				        
				}
			}
			rows.add(row);
		}
		in.close();
	}

	boolean found;
	int r1;
	int r2;
	int c1;
	int c2;

	void solve() {
		for (int i = 0; i < m; i++) {
		    for (int j = i + 1; j < m; j++) {
				checkRowPair(i, j);
			    if (found)
					return;
		    }
		}
	}

	static class Pair {
		String s1;
		String s2;

		Pair(String s1, String s2) {
			this.s1 = s1;
			this.s2 = s2;
		}

		@Override
		public boolean equals(Object o) {
			if (this == o)
				return true;
			if (!(o instanceof Pair))
				return false;

			Pair pair = (Pair)o;

			if (!s1.equals(pair.s1))
				return false;
			if (!s2.equals(pair.s2))
				return false;

			return true;
		}

		@Override
		public int hashCode() {
			int result = s1.hashCode();
			result = 31 * result + s2.hashCode();
			return result;
		}
	}

	private void checkRowPair(int i, int j) {
		Map<Pair, Integer> vals = new HashMap<Pair, Integer>();
		for (int k = 0; k < n; k++) {
			List<String> row = rows.get(k);
			Integer old = vals.put(new Pair(row.get(i), row.get(j)), k);
			if (old != null) {
				r1 = old;
				r2 = k;
				c1 = i;
				c2 = j;
				found = true;
				return;
			}
		}
	}

	void write() throws Exception {
		PrintWriter out = new PrintWriter("database.out");
		if (!found)
			out.println("YES");
		else {
			out.println("NO");
			out.printf("%d %d%n", r1 + 1, r2 + 1);
			out.printf("%d %d%n", c1 + 1, c2 + 1);
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

		public String nextLine() {
			assert line != null : "EOF";
			String result = line.substring(pos);
			try {
				line = in.readLine();
			} catch (IOException e) {
				throw new AssertionError("Failed to read line with " + e);
			}
			pos = 0;
			lineNo++;
			return result;
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
