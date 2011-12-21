import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2009 Problem C: Central Element
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class central_re {

	public static void main(String[] args) throws Exception {
		new central_re().go();
	}

	Scanner in = new Scanner(System.in);
	PrintStream out = System.out;

	int n;

	void go() throws Exception {
		readHeader();
		solve();
		writeAnswer();
	}

	enum Mode { LEFT, RIGHT }

	List<Integer> result = new ArrayList<Integer>();

	void solve() {
		List<Integer> all = new ArrayList<Integer>();
		for (int i = 1; i <= n; i++) {
			all.add(i);
		}
		if (n <= 3) {
			result = all;
			return;
		}
		List<Integer> left = find(all, Mode.LEFT);
		List<Integer> right = find(all, Mode.RIGHT);
		for (int i = 1; i <= n; i++) {
			int idx = left.indexOf(i);
			if (idx >= 0) {
				result.add(idx + 1);
				continue;
			}
			idx = right.indexOf(i);
			if (idx >= 0) {
				result.add(n - idx);
				continue;
			}
		    result.add(ask(Arrays.asList(left.get(0), right.get(0), i)));    
		}
	}

	class FindRes {
		List<Integer> bestpair = new ArrayList<Integer>();
		Integer helper;
		int bestval;
	}

	List<Integer> find(List<Integer> all, Mode mode) {
		assert all.size() >= 4;
		// first four
		FindRes r = find4(all, mode);
		// resolve remainder
		for (int i = 4; i < all.size(); i++) {
			Integer test = all.get(i);
			Integer b0 = r.bestpair.get(0);
			Integer b1 = r.bestpair.get(1);
			r = find4(Arrays.asList(b0, b1, r.helper, test), mode);
		}
		return r.bestpair;
	}

	private FindRes find4(List<Integer> all, Mode mode) {
		FindRes r = new FindRes();
		List<Integer> aa = new ArrayList<Integer>();
		for (int j = 0; j < 4; j++) {
			List<Integer> ask = new ArrayList<Integer>();
			for (int k = 0; k < 4; k++) {
				if (k != j)
					ask.add(all.get(k));
			}
			aa.add(ask(ask));
		}
		int min = Collections.min(aa);
		int max = Collections.max(aa);
		for (int j = 0; j < 4; j++) {
			Integer answer = aa.get(j);
			assert answer.equals(min) || answer.equals(max); // sanity check!
			if ((answer == min) ^ (mode == Mode.LEFT)) {
				r.bestpair.add(all.get(j));
			} else
				r.helper = all.get(j); // we'll need it for resolving
		}
		assert r.bestpair.size() == 2;
		r.bestval = mode == Mode.LEFT ? min : max;
		return r;
	}

	int ask(List<Integer> ask) {
		assert ask.size() == 3;
		for (int i = 0; i < ask.size(); i++) {
			if (i > 0)
				out.print(" ");
			out.print(ask.get(i));
		}
		out.println();
		in.nextLine();
		return in.nextInt();
	}

	private void readHeader() {
		n = in.nextInt();
		assert n >= 3 && n <= 200;
	}

	private void writeAnswer() {
		out.print("OK");
		for (Integer i : result) {
			out.print(" ");
			out.print(i);
		}
		out.println();
		out.flush();
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

		public Scanner(InputStream in) {
			this.in = new BufferedReader(new InputStreamReader(in));
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
