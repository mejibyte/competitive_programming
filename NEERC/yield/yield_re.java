/*
    Solution for NEERC'2005 Problem Y: Yield
    (C) Roman Elizarov
    Note: this solution attempts to check correctness of the input
*/

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class yield_re {
	static final int MAXABS = 1000;

	public static void main(String[] args) throws Exception {
		// Read input
		BufferedReader in = new BufferedReader(new FileReader("yield.in"));
		StringTokenizer st = new StringTokenizer(in.readLine());
		int a = Integer.parseInt(st.nextToken());
		int b = Integer.parseInt(st.nextToken());
		if (Math.abs(a) > MAXABS || Math.abs(b) > MAXABS)
			throw new IllegalArgumentException("a or b are out of range");
		if (st.hasMoreTokens())
			throw new IllegalArgumentException("Extra data on line");
		if (in.readLine() != null)
			throw new IllegalArgumentException("Extra data in file");
                in.close();

		// Write output
		PrintWriter out = new PrintWriter(new FileWriter("yield.out"));
		out.println(a + b);
		out.close();
	}
}
