/*
    Solution for NEERC'2008 Problem X: Xtrapolation
    (C) Roman Elizarov
    Note: this solution attempts to check correctness of the input
*/

import java.io.*;
import java.util.*;

public class xtra_re {
	private static final int MAX_NUM = 1000000000;
	private static final int MAX_COUNT = 1000;

	public static void main(String[] args) throws Exception {
		new xtra_re().go();
	}

	void go() throws Exception {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		PrintStream out = System.out;
		long sum = 0;
		int count = 0;
		while (true) {
			int num = Integer.parseInt(in.readLine());
			if (num == 0)
				break;
			assert num > 0 && num <= MAX_NUM;
			count++;
			assert count <= MAX_COUNT;
			sum += num;
			out.println(sum);
			out.flush();
		}
	}
}
