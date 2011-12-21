import java.util.*;
import java.math.BigInteger;

/**
 * Generates stress-tests for garbling
 *
 * @author Roman Elizarov
 */
public class gen_stress_garbling {
	private boolean FIND_LONGEST_LOOP = false;

	static class Field implements Cloneable {
		int[][] a;
		final int r;
		final int c;

		Field(int r, int c) {
			this.r = r;
			this.c = c;
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

	Random rnd = new Random();
	long besttime = System.currentTimeMillis();
	BigInteger besttotal = BigInteger.ZERO;

	public static void main(String[] args) {
		new gen_stress_garbling().go();
	}

	void go() {
		while (true) {
			generateAndAnalyzeOne();
		}
	}

	private void generateAndAnalyzeOne() {
		int r = 290 + rnd.nextInt(11);
		int c = 290 + rnd.nextInt(11);
		int pl = rnd.nextInt(101);
		int pr = rnd.nextInt(101 - pl);
		int seed = rnd.nextInt();
		char[][] map = genRandom(r, c, pl, pr, seed);
		Field f = new Field(r, c);
		garbleFieldOnce(f, map);
		BigInteger total = findLoopLength(f);
		if (total.compareTo(besttotal) > 0) {
			long time = System.currentTimeMillis();
			printMap(map);
			System.out.printf("-- Found %d with r=%d, c=%d, pl=%d, pr=%d, seed=%d in %d ms%n",
				total, r, c, pl, pr, seed, time - besttime);
			besttotal = total;
			besttime = time;
		}
	}

	private BigInteger findLoopLength(Field f) {
		// find transposition of one garbling
		int r = f.r;
		int c = f.c;
		int k = r * c;
		int[] transpose = new int[k];
		for (int i = 0; i < r; i++) {
		    for (int j = 0; j < c; j++) {
		        transpose[f.a[i][j]] = i * c + j;
		    }
		}
		// split transposition into loops
		int[] lnum = new int[k];
		int[] llen = new int[k];
		int lc = 0;
		Arrays.fill(lnum, -1);
		for (int p = 0; p < k; p++) {
		    if (lnum[p] < 0) {
			    int cnt = 0;
			    do {
				    cnt++;
				    lnum[p] = lc;
				    p = transpose[p];
			    } while (lnum[p] < 0);
				llen[lc++] = cnt;
		    }
		}
		// find total lenght
		BigInteger total = BigInteger.ONE;
		for (int q = 0; q < lc; q++) {
			if (FIND_LONGEST_LOOP)
				total = llen[q] > total.longValue() ? BigInteger.valueOf(llen[q]) : total;
			else
		        total = nok(total, BigInteger.valueOf(llen[q]));
		}
		return total;
	}

	private BigInteger nok(BigInteger a, BigInteger b) {
		return a.divide(a.gcd(b)).multiply(b);
	}

	private static char[][] genRandom(int r, int c, int pl, int pr, int seed) {
		char[][] map = new char[r - 1][c - 1];
		Random rnd = new Random(seed);
		for (int i = 0; i < r - 1; i++) {
			for (int j = 0; j < c - 1; j++) {
				int p = rnd.nextInt(100);
				if (p < pl)
					map[i][j] = 'L';
				else if (p < pl + pr)
					map[i][j] = 'R';
				else
					map[i][j] = 'N';
			}
		}
		return map;
	}

	private void garbleFieldOnce(Field f, char[][] map) {
		for (int i = 0; i < f.r - 1; i++) {
		    for (int j = 0; j < f.c - 1; j++) {
			    switch (map[i][j]) {
			    case 'L': f.garbleLeft(i, j); break;
			    case 'R': f.garbleRight(i, j); break;
			    }
		    }
		}
	}

	private void printMap(char[][] map) {
		for (char[] row : map) {
			System.out.println(new String(row));
		}
	}
}
