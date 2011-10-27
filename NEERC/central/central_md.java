import java.io.*;
import java.util.*;

public class central_md {
	private static Scanner in;
	private static PrintWriter out;
	
	private int ask() {
		return in.nextInt();
	}

	private int ask(int a, int b, int c) {
		out.println((a + 1) + " " + (b + 1) + " " + (c + 1));
		out.flush();
		return in.nextInt();
	}

	private void ok() {
		out.print("OK");
		for (int i = 0; i < n; i++) {
			out.print(" " + value[i]);
		}
		out.println();
		out.flush();
	}

	int n;
	int[] value;
	int a, b;
	int low, high;

	public void run() {
		n = ask();
		value = new int[n];
		if (n >= 6) {
			solveLarge();
		} else {
			solveSmall();
		}
		ok();
	}

	private void solveLarge() {
		findAB();
		List<Integer> small = new ArrayList<Integer>();
		List<Integer> large = new ArrayList<Integer>();
		for (int i = 0; i < n; i++) {
			if (i == a || i == b) {
				continue;
			}
			if (value[i] == low) {
				small.add(i);
			} else if (value[i] == high) {
				large.add(i);
			}
		}
		value[a] = ask(small.get(0), large.get(0), a);
		value[b] = value[a] ^ low ^ high;
		process(small, 1, 2);
		process(large, n - 1, n);
	}

	private void findAB() {
		for (a = 0; a < 10 && a + 1 < n; a += 2) {
			b = a + 1;
			if (tryAB()) return;
		}
		for (a = 0; a < 6; a++) {
			for (b = a + 1; b < 6; b++) {
				if (tryAB()) return;
			}
		}
	}

	private boolean tryAB() {
		low = n + 1;
		high = 0;
		int lowCount = 0;
		int highCount = 0;
		for (int i = 0; i < n; i++) {
			if (i == a || i == b) {
				continue;
			}
			value[i] = ask(a, b, i);
			if (value[i] < low) {
				low = value[i];
				lowCount = 1;
			} else if (value[i] == low) {
				lowCount++;
			}
			if (value[i] > high) {
				high = value[i];
				highCount = 1;
			} else if (value[i] == high) {
				highCount++;
			}
		}
		return low != high && lowCount > 1 && highCount > 1;
	}

	private void process(List<Integer> cells, int rest1, int rest2) {
		while (cells.size() >= 3) {
			int x = cells.get(cells.size() - 3);
			int y = cells.get(cells.size() - 2);
			int z = cells.get(cells.size() - 1);
			int xy = ask(x, y, a);
			int xz = ask(x, z, a);
			int yz = ask(y, z, a);
			int cell, val, index;
			if (xy == xz) {
				cell = x;
				val = xy;
				index = cells.size() - 3;
			} else if (xy == yz) {
				cell = y;
				val = xy;
				index = cells.size() - 2;
			} else {
				cell = z;
				val = xz;
				index = cells.size() - 1;
			}
			value[cell] = val;
			cells.remove(index);
		}
		value[cells.get(0)] = rest1;
		value[cells.get(1)] = rest2;
	}

	private void solveSmall() {
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				for (int k = j + 1; k < n; k++) {
					int v = ask(i, j, k);
					value[i] += v;
					value[j] += v;
					value[k] += v;
				}
			}
		}
		List<Integer> list = new ArrayList<Integer>();
		for (int i = 0; i < n; i++) {
			value[i] = n * value[i] + i;
			list.add(value[i]);
		}
		Collections.sort(list);
		for (int i = 0; i < n; i++) {
			value[i] = list.indexOf(value[i]) + 1;
		}
	}

	public static void main(String[] args) {
		Locale.setDefault(Locale.US);
		in = new Scanner(System.in);
		out = new PrintWriter(System.out);
		new central_md().run();
		in.close();
		out.close();
	}
}
