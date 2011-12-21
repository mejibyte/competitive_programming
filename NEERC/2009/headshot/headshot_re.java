import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2009 Problem H: Headshot
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class headshot_re {

	public static void main(String[] args) throws Exception {
		new headshot_re().go();
	}

	void go() throws Exception {
		read();
		solve();
		write();
	}

	String s;

	void read() throws Exception {
		Scanner in = new Scanner(new File("headshot.in"));
		in.useLocale(Locale.US);
		s = in.next();
		in.nextLine();
		assert s.matches("[01]{2,100}");
		assert s.contains("0");
		in.close();
	}

	enum Answer { EQUAL, ROTATE, SHOOT }

	Answer a;

	void solve() {
		int p1 = count("01");
		int q1 = count("0");
		int p2 = count("1");
		int q2 = s.length();
		int diff = p1 * q2 - p2 * q1;
		a = diff < 0 ? Answer.SHOOT : diff > 0 ? Answer.ROTATE : Answer.EQUAL;
	}

	private int count(String t) {
		int count = 0;
		String ss = s + s.substring(0, t.length() - 1);
		for (int i = 0; i < s.length(); i++) {
		    if (ss.substring(i, i + t.length()).equals(t))
			    count++;
		}
		return count;
	}

	void write() throws Exception {
		PrintWriter out = new PrintWriter("headshot.out");
		out.println(a);
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
