/*
    Solution for NEERC'2005 Problem Z: Zero-complexity Transposition
    (C) Roman Elizarov
    Note: this solution attempts to check correctness of the input
*/

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class zero_re {
	static final int MAXN = 10000;
	static final long MAXABS = 1000000000000000L;

	public static void main(String[] args) throws Exception {
		// Read input 
		BufferedReader in = new BufferedReader(new FileReader("zero.in"));
		int n = Integer.parseInt(in.readLine());
		if (n < 1 || n > MAXN) 
			throw new IllegalArgumentException("n is out of range");
		long[] a = new long[n];
		StringTokenizer st = new StringTokenizer(in.readLine());
		for (int i = 0; i < n; i++) {
			a[i] = Long.parseLong(st.nextToken());
			if (Math.abs(a[i]) > MAXABS)
				throw new IllegalArgumentException("a[i] is out of range");
		}
		if (st.hasMoreTokens())
			throw new IllegalArgumentException("Extra data on line");
		if (in.readLine() != null)
			throw new IllegalArgumentException("Extra data in file");
                in.close();

		// Write output
		PrintWriter out = new PrintWriter(new FileWriter("zero.out"));
		String sep = "";
		for (int i = n; --i >= 0;) {
			out.print(sep);
			sep = " ";
			out.print(a[i]);
		}
		out.close();
	}
}
