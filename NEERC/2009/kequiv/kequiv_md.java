import java.io.*;
import java.util.*;

public class kequiv_md {
	private static String fileName = kequiv_md.class.getSimpleName().replaceFirst("_.*", "");
	private static String inputFileName = fileName + ".in";
	private static String outputFileName = fileName + ".out";
	private static Scanner in;
	private static PrintWriter out;
	private final static int TEN = 10;
	
	class Intervals {
		ArrayList<Long> low = new ArrayList<Long>();
		ArrayList<Long> high = new ArrayList<Long>();
		int hash = 0;
		
		public void add(long lo, long hi) {
			if (lo < hi) {
				low.add(lo);
				high.add(hi);
			}
		}

		public Intervals setDigit(long ten, int d) {
			Intervals that = new Intervals();
			for (int i = 0; i < low.size(); i++) {
				that.add(above(low.get(i), ten, d), above(high.get(i), ten, d));
			}
			return that.normalize();
		}

		private Intervals normalize() {
			if (low.isEmpty()) {
				return this;
			}
			Intervals that = new Intervals();
			that.low.add(low.get(0));
			for (int i = 0; i < low.size() - 1; i++) {
				if (high.get(i) < low.get(i + 1)) {
					that.high.add(high.get(i));
					that.low.add(low.get(i + 1));
				}
			}
			that.high.add(high.get(high.size() - 1));
			return that;
		}
		
		@Override
		public boolean equals(Object obj) {
			Intervals that = (Intervals) obj;
			return low.equals(that.low) && high.equals(that.high);
		}
		
		@Override
		public int hashCode() {
			if (hash == 0) {
				hash = low.hashCode() * 179 + high.hashCode(); 
			}
			return hash;
		}
	}

	public Long above(long n, long ten, int d) {
		long a = n / ten;
		int c = (int) (a % 10);
		a /= 10;
		long b = n % ten;
		if (c < d) {
			return a * ten;
		}
		if (c > d) {
			return (a + 1) * ten;
		}
		return a * ten + b;
	}

	public void run() {
		Intervals a = new Intervals();
		int n = in.nextInt();
		for (int i = 0; i < n; i++) {
			a.add(in.nextLong(), in.nextLong() + 1);
		}

		boolean[][] differ = new boolean[TEN][TEN];
		for (long ten = 1; ten < a.high.get(a.high.size() - 1) && ten > 0; ten *= TEN) {
			int[] val = new int[TEN];
			HashMap<Intervals, Integer> results = new HashMap<Intervals, Integer>();
			for (int d = 1; d < TEN; d++) {
				Intervals b = a.setDigit(ten, d);
				Integer v = results.get(b);
				if (v == null) {
					v = results.size();
					results.put(b, v);
				}
				val[d] = v;
				for (int e = 1; e < d; e++) {
					if (val[d] != val[e]) {
						differ[e][d] = true;
					}
				}
			}
		}

		boolean[] printed = new boolean[TEN];
		for (int d = 1; d < TEN; d++) {
			if (printed[d]) {
				continue;
			}
			for (int e = d; e < TEN; e++) {
				if (!differ[d][e]) {
					out.print(e);
					printed[e] = true;
				}
			}
			out.println();
		}
	}

	public static void main(String[] args) throws IOException {
		Locale.setDefault(Locale.US);
		in = new Scanner(new FileReader(inputFileName));
		out = new PrintWriter(outputFileName);
		new kequiv_md().run();
		in.close();
		out.close();
	}
}
