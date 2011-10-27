import java.io.*;
import java.util.*;
import java.math.BigInteger;

/**
 * Solution for NEERC'2009 Problem G: Garbling Game.
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class garbling_re {
	static final int MODULO = 100000;

	public static void main(String[] args) throws Exception {
		new garbling_re().go();
	}

	void go() throws Exception {
		read();
		solve();
		write();
	}

	static class Field implements Cloneable {
		int[][] a;

		Field(int r, int c) {
			a = new int[r][c];
			int n = 0;
			for (int i = 0; i < r; i++) {
			    for (int j = 0; j < c; j++) {
			        a[i][j] = n++;
			    }
			}
		}

		void garbleLeft(int i, int j) {
			int t = a[i][j];
			a[i][j] = a[i][j + 1];
			a[i][j + 1] = a[i + 1][j + 1];
			a[i + 1][j + 1] = a[i + 1][j];
			a[i + 1][j] = t;
		}

		void garbleRight(int i, int j) {
			int t = a[i][j];
			a[i][j] = a[i + 1][j];
			a[i + 1][j] = a[i + 1][j + 1];
			a[i + 1][j + 1] = a[i][j + 1];
			a[i][j + 1] = t;
		}
	}

	int r;
	int c;
	BigInteger n;
	char[][] map;

	BigInteger turns = BigInteger.ZERO;
	int[] writtenModulo;
	int[] woneModulo;

	void read() throws Exception {
		Scanner in = new Scanner(new File("garbling.in"));
		in.useLocale(Locale.US);
		r = in.nextInt();
		c = in.nextInt();
		n = new BigInteger(in.next());
		in.nextLine();
		assert r >= 2 && r <= 300;
		assert c >= 2 && c <= 300;
		assert n.compareTo(BigInteger.ZERO) >= 0 && n.compareTo(BigInteger.valueOf(10).pow(100)) < 0;
		map = new char[r - 1][];
		for (int i = 0; i < r - 1; i++) {
			map[i] = in.next().toCharArray();
			in.nextLine();
			assert map[i].length == c - 1;
			for (int j = 0; j < c - 1; j++) {
				assert "RLN".indexOf(map[i][j]) >= 0;
			}
		}
		in.close();
	}

	void solve() {
		// garble field once
		int k = r * c;
		writtenModulo = new int[k];
		Field f = new Field(r, c);
		garbleFieldOnce(f);
		if (turns.compareTo(n) >= 0)
			return;
		// find transposition of one garbling
		int[] transpose = new int[k];
		for (int i = 0; i < r; i++) {
		    for (int j = 0; j < c; j++) {
		        transpose[f.a[i][j]] = i * c + j;     
		    }
		}
		// split transposition into loops
		int[] lnum = new int[k];
		int[] llen = new int[k];
		int[] lidx = new int[k];
		int[][] lfromidx = new int[k][0];
		int[][] lwrModulo = new int[k][0];
		int lc = 0;
		Arrays.fill(lnum, -1);
		for (int p = 0; p < k; p++) {
		    if (lnum[p] < 0) {
			    int cnt = 0;
			    do {
				    lnum[p] = lc;
				    lidx[p] = cnt;
				    lfromidx[lc] = grow(lfromidx[lc], cnt + 1);
				    lfromidx[lc][cnt] = p;
				    lwrModulo[lc] = grow(lwrModulo[lc], cnt + 2);
				    lwrModulo[lc][cnt + 1] = addModulo(lwrModulo[lc][cnt], writtenModulo[p]);
				    p = transpose[p];
				    cnt++;
			    } while (lnum[p] < 0);
				llen[lc++] = cnt;
		    }
		}
		woneModulo = writtenModulo.clone();
		// fast-forward full-field grablings
		BigInteger times = n.subtract(turns).divide(turns);
		int[] lrem = new int[k + 1];
		int[] lfltModulo = new int[k + 1];
		Arrays.fill(lrem, -1);
		for (int p = 0; p < k; p++) {
			int plnum = lnum[p];
			int pllen = llen[plnum];
			int plrem;
			int plfltModulo;
			if (lrem[pllen] >= 0) {
				plrem = lrem[pllen];
				plfltModulo = lfltModulo[pllen];
			} else {
				BigInteger pllenBig = BigInteger.valueOf(pllen);
				BigInteger flt = times.divide(pllenBig);
				plrem = lrem[pllen] = times.mod(pllenBig).intValue();
				plfltModulo = lfltModulo[pllen] = flt.mod(BigInteger.valueOf(MODULO)).intValue();
			}
			writtenModulo[p] = addModulo(writtenModulo[p], mulModulo(plfltModulo, lwrModulo[plnum][pllen]));
			int q = transpose[p];
			int idx1 = lidx[q];
			int idx2 = (idx1 + plrem) % pllen;
			q = lfromidx[plnum][idx2];
			if (idx2 > idx1) 
				writtenModulo[p] = addModulo(writtenModulo[p], lwrModulo[plnum][idx2] - lwrModulo[plnum][idx1] + MODULO);
			else if (idx2 < idx1)
				writtenModulo[p] = addModulo(writtenModulo[p],
					lwrModulo[plnum][pllen] - lwrModulo[plnum][idx1] + MODULO + lwrModulo[plnum][idx2]);
			f.a[q / c][q % c] = p;
		}
		turns = turns.add(times.multiply(turns));
		// finish remaining garblings
		garbleFieldOnce(f);
		assert turns.equals(n);
	}

	private int[] grow(int[] a, int size) {
		return a.length >= size ? a : Arrays.copyOf(a, Math.max(size, 2 * a.length));
	}

	void garbleFieldOnce(Field f) {
		for (int i = 0; i < r - 1; i++) {
		    for (int j = 0; j < c - 1; j++) {
			    if (turns.compareTo(n) >= 0)
			        return;
			    turns = turns.add(BigInteger.ONE);
			    writtenModulo[f.a[i][j]] = addModulo(writtenModulo[f.a[i][j]], 1);
			    switch (map[i][j]) {
			    case 'L': f.garbleLeft(i, j); break;
			    case 'R': f.garbleRight(i, j); break;
			    }
		    }
		}
	}

	static int mulModulo(int a, int b) {
		return (int)((long)a * b % MODULO);
	}

	static int addModulo(int a, int b) {
		return (a + b) % MODULO;
	}

	void write() throws Exception {
		PrintWriter out = new PrintWriter("garbling.out");
		for (int i = 0; i < r * c; i++) {
			out.println(writtenModulo[i]);
		}
		out.close();
	}

//----------------- just for validation ------------------

	/**
	 * Strict scanner to verify 100% correspondence between input files and input file format specification.
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
